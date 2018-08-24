//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       params-video-diff-prop.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace gens { namespace diff {
/**
  \brief  Структура хранит информацию о операции постобработки разности.
  */
struct ParamsVideoDiffProp
{
  ParamsVideoDiffProp ();

  virtual ~ParamsVideoDiffProp ();

  bool self_test () const;

  bool  enable_;            //< Флаг, включить постобработку вычисленной разности.
  short bound_filling_;      //< Значение границы, ниже или равно которой значения пикселей сбрасываются в 0.
  short val_filling_;        //< Значение пикселей, начальное значение которых больше границы.


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}}}      // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::gens::diff::ParamsVideoDiffProp);
