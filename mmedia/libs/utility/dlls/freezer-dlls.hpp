#pragma once
/**
\file       freezer-dlls.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/
namespace libs::utility::dlls
{
/// Тип для гарантированного удеражания в памяти всех загруженных модулей, даже если они уже не нужны
/// Количество расхода памяти при этом незначительно (несколько десятков мегабайт в худшем случае)
/// И при этом мы избегаем сбоев при работе с объектами, порожденными различными модулями
class FreezerDlls final
{
  public:
  U3_ADD_DELETE_MOVE_COPY (FreezerDlls)

  FreezerDlls ()  = default;
  ~FreezerDlls () = default;

  void add (const std::string& name, const dll_type& lib);

  private:
  //  internal typess
  using dlls_type = boost::unordered_flat_map< std::string, dll_type >;
  using sync_type = std::mutex;
  using lock_type = std::scoped_lock< sync_type >;

  std::mutex mtx_;    //< Синх. поле для доступу к объекту, т.к. он может (и должен) максимально быть разделимым в процессе
  dlls_type  dlls_;   //< Все загруженные модули
};
}   // namespace libs::utility::dlls
