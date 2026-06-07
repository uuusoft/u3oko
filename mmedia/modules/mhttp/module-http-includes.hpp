#pragma once
/**
\file       module-http-includes.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    mhttp
*/
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "appl/web-shared-state.hpp"

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

#include "appl/consts/module-http-const-vals.hpp"
#include "appl/http-module-syn.hpp"
#include "appl/skip-data-state.hpp"
#include "appl/id2buf-info.hpp"

#include "appl/impl/beast/beast-handle-request-func.hpp"
#include "appl/impl/beast/beast-websocket-session.hpp"
#include "appl/impl/beast/beast-http-session.hpp"
#include "appl/impl/beast/beast-websocket-session-ssl.hpp"
#include "appl/impl/beast/beast-http-session-ssl.hpp"
// #include "appl/impl/beast/beast-session.hpp"
#include "appl/impl/beast/beast-listener.hpp"
#include "appl/impl/common/server_certificate.hpp"

#include "appl/http-module.hpp"
#include "appl/helpers/module-http-includes-helpers.hpp"
