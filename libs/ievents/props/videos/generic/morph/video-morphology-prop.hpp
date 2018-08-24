//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       video-morphology-prop.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generic { namespace morph {
/**
  \brief  Перечисление морфологических операций над изображением.
  */
enum struct TypeOperation
{
  empty    = 0,      //< Пустая операция, точнее ее отсутствие. Используется для тестов (скорости/стабильности).
  erosion  = 1,      //< Операция эрозии.
  dilation = 2,      //< Операция дилатации.
  binary   = 4       //< Операция бинаризации.
};
/**
  \brief  empty brief
  */
struct ParamsOperation
{
  ParamsOperation () :
    size_spot_ (1),
    bound_filling_ (0),
    type_ (TypeOperation::empty),
    val_filling_ (1)
  {}

  bool
  self_test () const
  {
    CHECK_STATE (size_spot_ <= 11, "invalid size spot, " << size_spot_);
    return true;
  }

  TypeOperation type_;              //< Тип операции.
  short         size_spot_;         //< Размер ядра операции.
  short         bound_filling_;      //< Значение границы бинаризации.
  short         val_filling_;        //< ???


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (type_);
    ar& BOOST_SERIALIZATION_NVP (size_spot_);
    ar& BOOST_SERIALIZATION_NVP (bound_filling_);
    ar& BOOST_SERIALIZATION_NVP (val_filling_);
    return;
  }
};
/**
  \brief  empty brief
  */
struct BuffInfo
{
  //  ext types
  using ops_type = std::vector<ParamsOperation>;

  BuffInfo () :
    bindx_diff_ (utils::dbuffs::video::consts::offs::invalid)
  {
    ops_.reserve (8);
  }

  off_buff_type bindx_diff_;      //< ???
  ops_type      ops_;             //< ???


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (bindx_diff_);
    ar& BOOST_SERIALIZATION_NVP (ops_);
    return;
  }
};
/**
  \brief  Свойства фильтра для реализации морфологических операций над изображением.
  */
class VideoMorphologyProp : public ievents::Event
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
  using type2buff_type = std::list<std::pair<off_buff_type, BuffInfo>>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoMorphologyProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoMorphologyProp);
  UUU_DISABLE_ACOPY_TYPE (VideoMorphologyProp);

  explicit VideoMorphologyProp (const Acessor& = Acessor (0));

  virtual ~VideoMorphologyProp ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/morph/video-morphology-prop";
    return _ret;
  }

  type2buff_type diffs_;      //< ???


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generic::morph

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::morph::VideoMorphologyProp);
