//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       morph-buff-info.hpp
\date       10.09.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generic { namespace morph {
/**
\brief  Тип для группировки параметров морфологической операции над одним буфером.
*/
struct MorphBuffInfo
{
  //  ext types
  using ops_type = std::vector<MorphOperationParams>;

  MorphBuffInfo () :
    bindx_diff_ (utils::dbuffs::video::consts::offs::invalid)
  {
    ops_.reserve (8);
  }

  MorphBuffInfo (const off_buff_type& _bindx_diff, const MorphOperationParams& _op) :
    bindx_diff_ (_bindx_diff)
  {
    ops_.push_back (_op);
  }

  off_buff_type bindx_diff_;      //< Индекс буфера
  ops_type      ops_;             //< Тип морфологической операции над буфером.


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

}}}}}}      // namespace libs::ievents::props::videos::generic::morph
