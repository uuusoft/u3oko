//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       buff-event-info.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace motion_est {
/**
  \brief  empty brief
  */
struct BuffEventInfo : public ::libs::events::buff::BuffEventInfo
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };

  public:
  //  ext types
  using vectors_type = std::vector<std::pair<char, char>>;

  explicit BuffEventInfo (const Acessor& = Acessor (0)) :
    max_error_ (16.0f * 16.0f * 10.0f),
    min_error_ (0.0f),
    size_block_ (16),
    size_search_ (16)
  {}

  void check () const;

  float        max_error_;        //< Ошибка блока, больше которой нельзя считать блок найденным
  float        min_error_;        //< Минимальная ошибка блока, меньше или равно которой можно считать, что данный блок равен текущему. Т.е. дальнейшний поиск можно не производить.
  short        size_block_;       //< Размер блока в пикселях, для которого производится оценка движения.
  short        size_search_;      //< Размер области поиска в пикселях.
  vectors_type search_vecs_;      //< Вычисленные по области поиска или предзагруженные вектора поиска, которые определяют порядок поиска.


  protected:
  virtual void load_int (const base_functs::xml::itn& _node) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::buff::BuffEventInfo);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}}}      // namespace libs::ievents::props::videos::generics::motion_est

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::motion_est::BuffEventInfo);
