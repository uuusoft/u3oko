#pragma once
/**
\file       links-application.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_properties_libs
*/

namespace libs::properties::vers::links::mids
{
using key_storage_type = std::pair< libs::link::details::ModuleLinks, libs::link::details::ModuleLinks >;

constexpr key_storage_type appl2log { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::log };
constexpr key_storage_type log2appl { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::appl };

constexpr key_storage_type http2appl { libs::link::details::ModuleLinks::http, libs::link::details::ModuleLinks::appl };
constexpr key_storage_type http2log { libs::link::details::ModuleLinks::http, libs::link::details::ModuleLinks::log };
constexpr key_storage_type log2http { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::http };
constexpr key_storage_type appl2http { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::http };

constexpr key_storage_type mdata2appl { libs::link::details::ModuleLinks::mdata, libs::link::details::ModuleLinks::appl };
constexpr key_storage_type mdata2log { libs::link::details::ModuleLinks::mdata, libs::link::details::ModuleLinks::log };
constexpr key_storage_type log2mdata { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::mdata };
constexpr key_storage_type appl2mdata { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::mdata };

constexpr key_storage_type gui2appl { libs::link::details::ModuleLinks::gui, libs::link::details::ModuleLinks::appl };
constexpr key_storage_type gui2log { libs::link::details::ModuleLinks::gui, libs::link::details::ModuleLinks::log };
constexpr key_storage_type log2gui { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::gui };
constexpr key_storage_type appl2gui { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::gui };

constexpr key_storage_type events2appl { libs::link::details::ModuleLinks::events, libs::link::details::ModuleLinks::appl };
constexpr key_storage_type log2events { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::events };
constexpr key_storage_type events2log { libs::link::details::ModuleLinks::events, libs::link::details::ModuleLinks::log };
constexpr key_storage_type appl2events { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::events };

constexpr key_storage_type storage2appl { libs::link::details::ModuleLinks::storage, libs::link::details::ModuleLinks::appl };
constexpr key_storage_type storage2log { libs::link::details::ModuleLinks::storage, libs::link::details::ModuleLinks::log };
constexpr key_storage_type log2storage { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::storage };
constexpr key_storage_type appl2storage { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::storage };

constexpr key_storage_type network2appl { libs::link::details::ModuleLinks::network, libs::link::details::ModuleLinks::appl };
constexpr key_storage_type network2log { libs::link::details::ModuleLinks::network, libs::link::details::ModuleLinks::log };
constexpr key_storage_type log2network { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::network };
constexpr key_storage_type appl2network { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::network };

constexpr key_storage_type unknown { libs::link::details::ModuleLinks::unknown, libs::link::details::ModuleLinks::unknown };
}   // namespace libs::properties::vers::links::mids

namespace libs::properties::vers::links
{
struct pair_hash {
  template< class T1, class T2 >
  std::size_t
  operator() (const std::pair< T1, T2 >& p) const
  {
    const auto h1 = std::hash< std::uint32_t > {}(U3_CAST_UINT32_FORCE (p.first));
    const auto h2 = std::hash< std::uint32_t > {}(U3_CAST_UINT32_FORCE (p.second));
    return U3_CAST_UINT32_FORCE (h1) ^ (U3_CAST_UINT32_FORCE (h2) << 1);
  }
};

/// Структура для группировки связей модуля
/// link_ptr_type тип хранимого указателя, у владельцев он shared, у агрегатов weak
template< typename TTLinkPtr >
struct LinksApplication final {
  public:
  //  ext types
  using link_ptr_type      = TTLinkPtr;                                                          //<
  using key_storage_type   = libs::properties::vers::links::mids::key_storage_type;              //<
  using links_storage_type = std::unordered_map< key_storage_type, link_ptr_type, pair_hash >;   //<

  LinksApplication () = default;

  ~LinksApplication ()
  {
    reset ();
  }

  template< typename TTLinkPtrRsp >
  void
  copy_links (const LinksApplication< TTLinkPtrRsp >& rsh)
  {
    std::scoped_lock lock (threadsan_mtx_, rsh.threadsan_mtx_);
    module_links_.clear ();
    for (const auto& [key, val] : rsh.module_links_)
    {
      module_links_[key] = val;
    }
  }

  void
  reset () noexcept
  {
    std::scoped_lock lock (threadsan_mtx_);
    module_links_.clear ();
  }

  bool
  self_test () const
  {
    return true;
  }

  const TTLinkPtr
  get (const key_storage_type& key) const
  {
    std::scoped_lock lock (threadsan_mtx_);
    auto             finger = module_links_.find (key);
    U3_CHECK (finger != module_links_.end (), "failed get link to module");
    return finger->second;
  }

  void
  set (const key_storage_type& key, const TTLinkPtr& ptr)
  {
    std::scoped_lock lock (threadsan_mtx_);
    module_links_[key] = ptr;
  }

  void
  reset_link (const key_storage_type& key)
  {
    std::scoped_lock lock (threadsan_mtx_);
    auto             finger = module_links_.find (key);
    U3_CHECK (finger != module_links_.end (), "failed get link to module");
    return finger->second.reset ();
  }

  // EAI-REFACT -> private
  // private:
#ifdef U3_FORCE_SYNC_FOR_THREAD_SANITIZER
  using sync_type = std::mutex;
#else
  using sync_type = ::libs::helpers::thread::EmptyMutex;
#endif

  mutable sync_type  threadsan_mtx_;   //< чтобы успокоить thread sanitizer, т.к. объекты этого типа могут использоваться повторно то и в разных потоках но с разделением по времени
  links_storage_type module_links_;    //<
};
}   // namespace libs::properties::vers::links
