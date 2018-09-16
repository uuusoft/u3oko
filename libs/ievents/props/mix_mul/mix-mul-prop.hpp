#pragma once
/**
\file       mix-mul-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace mix_mul {
/**
\brief  empty brief
 */
class MixMulProp : public ievents::Event
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
  // ext types
  using out_channels_type = std::array<OutChannelInfo, consts::max_output_points>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (MixMulProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MixMulProp);
  UUU_DISABLE_ACOPY_TYPE (MixMulProp);

  explicit MixMulProp (const Acessor& = Acessor (0));

  virtual ~MixMulProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/mix_mul/mix-mul-prop";
    return _ret;
  }

  out_channels_type outs_;      //< У фильтра-размножителя можно задать для каждой выходной точки свой уникальный список умножения буферов. Эта структура и хранит их.


  protected:
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  void load_out (const base_functs::xml::itn& _node, OutChannelInfo* _prop);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}      // namespace libs::ievents::props::mix_mul

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::mix_mul::MixMulProp);
