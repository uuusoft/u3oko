#pragma once
/**
\file       libs-iproperties-syn.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_iproperties_lib
*/

namespace libs::iproperties::syn
{
using ISharedProperty        = ::libs::properties::ISharedProperty;
using ISharedPropertyStorage = ::libs::properties::ISharedPropertyStorage;
using BlockMemAllocatorProxy = ::utils::mem_funcs::impl::BlockMemAllocatorProxy;
using BufAllocatorProxy      = ::utils::dbufs::allocator::BufAllocatorProxy;
using ApplicationProp        = ::libs::ievents::props::application::ApplicationProp;
using PropertyLogModuleEvent = ::libs::ievents::props::modules::log::PropertyLogModuleEvent;
using VideoDriverCaptureProp = ::libs::ievents::props::videos::generic::driver::VideoDriverCaptureProp;
using key_property_type      = ::libs::properties::consts::keys::key_property_type;
}   // namespace libs::iproperties::syn
