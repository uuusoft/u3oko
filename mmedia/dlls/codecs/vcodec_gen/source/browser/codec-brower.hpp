#pragma once
/**
\file       codec-brower.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_vcodec_gen
\brief      Интерфейс объекта поиска кодеков в системе
*/

namespace dlls::codecs::vcodec_gen::browser
{
/// Класс для хранения информации о доступных видеокодеках в системе
class CodecBrower final
{
  public:
  CodecBrower ()                                  = default;
  ~CodecBrower ()                                 = default;
  CodecBrower (const CodecBrower& src)            = delete;
  CodecBrower& operator= (const CodecBrower& src) = delete;

  /// Функция возвращает по идентификатору имя файла с кодеком или пусто
  /// \param[in]  id идентификатор кодека
  /// \return     имя файла
  std::string get_codec (const libs::helpers::uids::minor::id_val& id);

  private:
  //  internal typess
  using sync_type        = std::mutex;
  using lock_type        = std::scoped_lock< sync_type >;
  using format2file_type = std::unordered_multimap< libs::helpers::uids::minor::id_val, std::string >;

  /// Функция обновляет список кодеков
  void refresh_list_codecs ();

  sync_type        mtx_;                 //< Т.к у объкту возможен доступ из разных потоков, кладем объект для синхронизации доступа
  bool             refreshed_ = false;   //< Флаг, список кодеков обновлен
  format2file_type format2file_;         //< Поле для пребразования guid в имя файла
};
}   // namespace dlls::codecs::vcodec_gen::browser
