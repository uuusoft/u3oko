#pragma once
/**
\file       libs-iproperties-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_iproperties_lib
*/

namespace libs::iproperties::syn
{
using ISharedProperty        = ::libs::properties::ISharedProperty;
using ISharedPropertyStorage = ::libs::properties::ISharedPropertyStorage;
using BlockMemAllocatorProxy = ::utils::mems::impl::BlockMemAllocatorProxy;
using BufAllocatorProxy      = ::utils::dbufs::allocator::BufAllocatorProxy;
using ApplicationProp        = ::libs::events_base::props::application::ApplicationProp;
using PropertyLogModuleEvent = ::libs::events_base::props::modules::log::PropertyLogModuleEvent;
using VideoDriverCaptureProp = ::libs::events_base::props::videos::generic::driver::VideoDriverCaptureProp;
using key_property_type      = ::libs::properties::consts::keys::key_property_type;
}   // namespace libs::iproperties::syn
