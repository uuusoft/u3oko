#pragma once
/**
\file       create-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_link
*/

namespace libs::link
{
/// Структура для группировки информации для создания реализации "связь" между модулями
/// Параметры определяют имя сервиса для настроек и данных, способ загрузки кода, имя модуля и пр.
/// Более подробно по ключам consts::text::id_
struct CreateInfo {
  //  ext types
  using val_type    = std::variant< bool, std::string, std::uint64_t, details::ModuleLinks, details::CodeRuns >;
  using val_id_type = std::string;
  using vals_type   = boost::unordered_flat_map< val_id_type, val_type >;

  CreateInfo ()          = default;
  virtual ~CreateInfo () = default;
  explicit CreateInfo (const vals_type& vals);

  auto check () const -> void;
  auto get_prefix () const -> std::string;

  mutable vals_type link_params_;   //<
};

auto to_string (const CreateInfo& val) -> std::string;
}   // namespace libs::link

namespace libs::link::helpers
{
auto get_module_links (const CreateInfo& info) -> details::ModuleLinks;
auto get_code_runs (const CreateInfo& info) -> details::CodeRuns;
auto get_server_side (const CreateInfo& info) -> bool;
}   // namespace libs::link::helpers
