//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       morph-operation-params.hpp
\date       10.09.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generic { namespace morph {
/**
\brief  Группировка параметров одной морфологической операции.
*/
struct MorphOperationParams
{
  MorphOperationParams (
    const MorphOperationType& _type          = MorphOperationType::empty,
    const short               _size_spot     = 1,
    const short               _bound_filling = 0,
    const short               _val_filling   = 1) :

    size_spot_ (_size_spot),
    bound_filling_ (_bound_filling),
    type_ (_type),
    val_filling_ (_val_filling)
  {}

  bool
  self_test () const
  {
    CHECK_STATE_RET (size_spot_ <= 11, "invalid size spot, " << size_spot_, false);
    return true;
  }

  MorphOperationType type_;               //< Тип операции.
  short              size_spot_;          //< Размер ядра операции.
  short              bound_filling_;      //< Значение границы бинаризации.
  short              val_filling_;        //< Значение заполнения после бинаризации.


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

}}}}}}      // namespace libs::ievents::props::videos::generic::morph
