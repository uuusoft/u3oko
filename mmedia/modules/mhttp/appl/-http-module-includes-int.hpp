#pragma once
/**
\file       -http-module-includes-int.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
*/
#include "mmedia/includes/control-defines-includes.hpp"
// EAI-REFACT
#include <regex>
#include <queue>

#include "mmedia/includes/includes.hpp"
#include "../../-modules-includes-int.hpp"
#include "mmedia/dnodes/terminals/video_sender/consts/video-sender-const-vals.hpp"
#include "mmedia/libs/icore/impl/base/-libs-icore-impl-base-includes.hpp"

#include "mmedia/dnodes/codecs/codec_funcs/codec-funcs-includes.hpp"
#include "mmedia/dnodes/codecs/codec_funcs/bitgen/codec-funcs-bitgen-includes.hpp"
#include "mmedia/dnodes/codecs/codec_gen/codec-gen-includes.hpp"

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

#include "-http-module-const-vals.hpp"
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

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG ::libs::ilink::consts::id_http_log
