/**
\file       data-module-helpers-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_module_data
*/

namespace modules::uuu_mdata::appl::helpers
{
inline std::string
make_file_name_for_save_event (
  const syn::NodeID::name_id_type& id_node,
  const std::string&               id_event)
{
  auto ret = id_node + "+" + ::libs::helpers::files::prepare_for_file_name (id_event);
  return ret;
}

inline void
split_event_file_name2parts (
  const std::string&         file_name,
  syn::NodeID::name_id_type& id_node,
  std::string&               id_event)
{
  id_node.clear ();
  id_event.clear ();

  auto pos_plus = file_name.find ('+');
  auto pos_dot  = file_name.find_last_of ('.');

  if (std::string::npos == pos_plus ||
      std::string::npos == pos_dot ||
      pos_dot <= pos_plus)
  {
    U3_LOG_DATA_ERROR ("invalid event file name" + TOLOG (file_name));
    return;
  }

  id_node  = file_name.substr (0, pos_plus);
  id_event = file_name.substr (pos_plus + 1, pos_dot - pos_plus - 1);

  std::transform (
    id_event.begin (),
    id_event.end (),
    id_event.begin (),
    [] (char val) -> char {
      return val == ::libs::helpers::files::consts::special_convert_path_symbol ? '/' : val;
    });
}
}   // namespace modules::uuu_mdata::appl::helpers
