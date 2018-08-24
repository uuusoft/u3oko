#pragma once
/**
\file       syn.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.06.2018.
\copyright  www.uuusoft.com
\project    uuu_gen_lib
\brief      empty brief
*/

namespace dlls { namespace sources { namespace gen_lib {
//  syn
using ::libs::ievents::props::videos::generics::driver::VideoDriverProp;
using ::libs::ievents::props::videos::generics::driver::VideoDriverCaptureProp;
using ::libs::ievents::props::videos::generics::driver::LinksVideoDriverProp;
using ::libs::icore::impl::var1::obj::FilterInfo;
using ::utils::dbuffs::video::IVideoBuff;
using ::libs::helpers::sys::cpu::TypeExtCpu;
using ::utils::dbuffs::video::consts::offs::off_buff_type;

using transform_events_type = std::list<::libs::events::IEvent::ptr>;
using keys2buffs_type       = std::unordered_map<off_buff_type, IVideoBuff::ptr>;
using keys2buffs_ptr_type   = std::shared_ptr<keys2buffs_type>;

}}}      // namespace dlls::sources::gen_lib
