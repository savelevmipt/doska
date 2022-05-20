#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include "view/Camera.h"
#include "selectors/MouseState.h"
#include <boost/thread/thread.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <queue>

#include "global_variables.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
std::queue <std::string> msg_to_send;


class writing{
public:
    writing(std::shared_ptr< websocket::stream<tcp::socket> >& ws, std::shared_ptr<Camera> cam) :ws(ws){}

    void operator() () {
        beast::flat_buffer buffer;
        while (true) {
            while(msg_to_send.empty()) {
            }
            buffer.clear();
            auto msg = msg_to_send.front();
            msg_to_send.pop();
            ws->write(net::buffer(msg));
        }
    }
private:
    std::shared_ptr< websocket::stream<tcp::socket> > ws;
};

class reading {
public:
    reading(std::shared_ptr< websocket::stream<tcp::socket> >& ws, std::shared_ptr<Camera> cam) :ws(ws), cam(cam){}

    void operator() () {
        beast::flat_buffer buffer;
        while (true) {
            buffer.clear();
            ws->read(buffer);
            std::cout << beast::make_printable(buffer.data()) << std::endl;
            handle_message(beast::buffers_to_string(buffer.data()));
        }
    }
private:
    std::shared_ptr< websocket::stream<tcp::socket> > ws;
    std::shared_ptr<Camera> cam;

    void handle_message(std::string msg) {
        std::cout << "__" + msg << std::endl;
        std::vector <std::string> split_vec;
        split(split_vec, msg.substr(1, msg.size()), boost::algorithm::is_any_of("$"));
        if (msg[0] == 'C') { //Curve
            Position last, curr;

            last.flop.x = std::atof(split_vec[0].data());
            last.flop.y = std::atof(split_vec[1].data());
            last.intp.x = std::atoi(split_vec[2].data());
            last.intp.y = std::atoi(split_vec[3].data());

            curr.flop.x = std::atof(split_vec[4].data());
            curr.flop.y = std::atof(split_vec[5].data());
            curr.intp.x = std::atoi(split_vec[6].data());
            curr.intp.y = std::atoi(split_vec[7].data());

            cam->doska2.addLine(last, curr);
        }
        else if (msg[0] == 'R'){ //Rectangle
            Square* square = new Square;
            square->center.x =  std::atof(split_vec[0].data());
            square->center.y =  std::atof(split_vec[1].data());
            square->size.x =  std::atof(split_vec[2].data());
            square->size.y =  std::atof(split_vec[3].data());
            IntPosition chunk(std::atoi(split_vec[4].data()), std::atoi(split_vec[5].data()));
            cam->doska2.addObject(square, chunk);
        }
    }
};

int main(int argc, char** argv) {

    std::string host = "localhost";
    std::string port = "8083";
    net::io_context ioc;
    tcp::resolver resolver{ioc};
    auto ws = std::make_shared<websocket::stream<tcp::socket>> (ioc);
    auto const results = resolver.resolve(host, port);
    auto ep = net::connect(ws->next_layer(), results);
    host += ':' + std::to_string(ep.port());
    ws->set_option(websocket::stream_base::decorator(
            [](websocket::request_type& req)
            {
                req.set(http::field::user_agent,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            }));
    ws->handshake(host, "/");



    if(SDL_Init(SDL_INIT_VIDEO)){
        std::cout << "Error initialising\n";
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Doska",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             1280, 720,
                             SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    if(window == nullptr){
        std::cout << "Error making window\n";
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Doska2 doska;
    auto cam = std::make_shared<Camera> (renderer, doska);
    Camera& camera = *cam;
    camera.setSize(1280, 720);

    writing writing_object(ws, cam);
    std::thread writing_thread{writing_object};

    reading reading_object(ws, cam);
    std::thread reading_thread{reading_object};

    MouseState state(camera);
    SDL_Event event;
    bool running = true;

    while(running){
        while(!SDL_PollEvent(&event))
            camera.renderAll();

        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT: {
                switch(event.window.event) {
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        camera.setSize(event.window.data1, event.window.data2);
                        break;
                }
                break;
            }
            case SDL_KEYDOWN: {
                switch(event.key.keysym.scancode){
                    case SDL_SCANCODE_A: {
                        state.key_state = STATE_DRAW_LINE;
                        break;
                    }
                    case SDL_SCANCODE_S: {
                        state.key_state = STATE_MOVE;
                        break;
                    }
                    case SDL_SCANCODE_D: {
                        state.key_state = STATE_DELETE;
                        break;
                    }
                    case SDL_SCANCODE_R:{
                        state.key_state = STATE_DRAW_RECT;
                        break;
                    }
                    case SDL_SCANCODE_E:{
                        state.key_state = STATE_COPY;
                        break;
                    }
                    case SDL_SCANCODE_W:{
                        state.key_state = STATE_RESIZE;
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
                state.x = event.button.x;
                state.y = event.button.y;
                if(event.button.button == 1) {
                    state.left_pressed = true;
                    if(camera.selector == nullptr)
                        camera.selector = state.selectors[state.key_state];
                    camera.selector->begin(camera.getPosition(state.x, state.y));
                }
                break;
            case SDL_MOUSEBUTTONUP: {
                if (event.button.button == 1) {
                    state.left_pressed = false;
                    if(camera.selector != nullptr){
                        if(camera.selector->finish())
                            camera.selector = nullptr;
                    }
                }
                break;
            }
            case SDL_MOUSEWHEEL:
                if(floorf(event.wheel.preciseY) == ceilf(event.wheel.preciseY) && event.wheel.preciseY != 0){
                    camera.zoom(state.x, state.y, event.wheel.preciseY);
                }else{
                    camera.pos += Vector2(event.wheel.preciseX, event.wheel.preciseY) * (100 / camera.scale);
                    camera.pos.floor();
                }
                break;
            case SDL_MOUSEMOTION: {
                state.x = event.motion.x;
                state.y = event.motion.y;
                if (!state.left_pressed)
                    break;
                if(camera.selector != nullptr)
                    camera.selector->update(camera.getPosition(state.x, state.y));
                break;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
