#pragma once
/**
\file       -http-module-includes.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
*/
#define BOOST_SPIRIT_THREADSAFE

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "web-shared-state.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/beast/version.hpp>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/strand.hpp>
#include <boost/make_unique.hpp>
#include <boost/optional.hpp>

#include "consts/module-http-const-vals.hpp"
#include "-http-module-syn.hpp"
#include "helpers/skip-data-state.hpp"

#include "impl/beast/beast-handle-request-func.hpp"
#include "impl/beast/beast-websocket-session.hpp"
#include "impl/beast/beast-http-session.hpp"
#include "impl/beast/beast-websocket-session-ssl.hpp"
#include "impl/beast/beast-http-session-ssl.hpp"
// #include "impl/beast/beast-session.hpp"
#include "impl/beast/beast-listener.hpp"
#include "impl/common/server_certificate.hpp"

#include "http-module.hpp"
#include "helpers/module-http-includes-helpers.hpp"
