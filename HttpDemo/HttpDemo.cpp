// HttpDemo.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "httplib.h"
#include <iostream>
#include "BoundingRect.hpp"

#pragma warning(disable:4996)

int main(int argc, char* argv[]) {

//   WORD sockVersion = MAKEWORD(2, 2);
//   WSADATA wsaData;
//   if (WSAStartup(sockVersion, &wsaData) != 0)
//   {
//     return 0;
//   }

  std::string str;
  std::cin >> str;
  BoundingRect crt(str);





  //http

  using namespace httplib;
  Server svr;
  svr.Get("/hi", [](const Request& req, Response& res) {
    res.set_content("Hello World!", "text/plain");
  });

  svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
  });

  svr.Get("/body-header-param", [](const Request& req, Response& res) {
    if (req.has_header("Content-Length")) {
      auto val = req.get_header_value("Content-Length");
    }
    if (req.has_param("key")) {
      auto val = req.get_param_value("key");
    }
    res.set_content(req.body, "text/plain");
  });

  svr.Get("/stop", [&](const Request& req, Response& res) {
    svr.stop();
  });
  svr.Get("/", [&](const Request& req, Response& res) {
    res.set_content("welcome", "text/plain");
  });
  svr.listen("localhost", 1234);
  WSACleanup();
  return 0;
}

