#pragma once
/**
\file       core.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       22.12.2016.
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      Объявление реализации ядра по обработке данных.
*/

namespace libs { namespace icore { namespace impl { namespace var1 {
//  syn
using ::libs::core::path::IPath;
using ::libs::core::ICore;
/**
\brief  Локальная (внутрипроцессная) реализация внешнего интерфейса ядра.
*/
class Core : public ICore
{
  public:
  //  ext types
  using out_wpaths_type = std::list<IPath::weak_ptr>;

  Core ();

  virtual ~Core ();


  private:
  //  int types
  using sync_type  = std::mutex;
  using guard_type = std::lock_guard<sync_type>;
  using paths_type = std::list<IPath::ptr>;

  //  ICore impl
  virtual IPath::weak_ptr create_path_int () override;
  virtual void            get_paths_int (out_wpaths_type& _paths) override;
  virtual bool            delete_path_int (IPath::weak_ptr _obj) override;
  /**
  \brief  Функция удаления всех графов обработки данных.
          Ожидается, что при ее вызове никаких клиентов ядра уже не существует.
  */
  void delete_paths ();

  paths_type paths_;      //< Все существующие пути ядра.
  sync_type  mtx_;        //< Для синхронизации доступа к объекту
};

}}}}      // namespace libs::icore::impl::var1
