//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-module-work-funct.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes_int.hpp"
#include "base-module.hpp"
//  old shit
namespace libs { namespace ilink { namespace appl { namespace base {

#if 0
  void BaseModule::work_int()
  {

    try
    {
      ::libs::link::ILink::ptr _srss[] = 
      {
        links_.appl2gui_,
        links_.appl2data_,
        links_.appl2http_
        //links_.appl2appl_???
      };

      list_catch_msg_funct_type _functs;

      do
      {
        bool _recv_msg  = false;

        for( auto& _src : _srss )
        {
          auto _msg = _src ? _src->received_msg() : IEvent::ptr();

          if( !_msg )
          {
            continue;
          }

          _recv_msg = true;

          current_seq_.reset();

          auto _last_msg = _msg;
          //Прямая сборка стека функций для обработки данного сообщения.
          //Формируем описание запроса (все флаги, транзакцию и прочее).
          while( _msg )
          {
            auto          _find = catch_functs_.find (_msg->get_type_id ());
            catch_msg_funct_type  _funct = std::bind ( &BaseModule::default_catch_funct, this, std::placeholders::_1, std::placeholders::_2 );

            if ( catch_functs_.end () != _find )
            {
              _funct = _find->second;
            }

            _functs.push_back( std::make_pair(_funct, _msg) );

            _msg = _funct ( _msg, true );

            _last_msg = _msg ? _msg : _last_msg;
          }

          UASSERT( !_functs.empty() );
          //Инверсная обработка сообщения через стек функций.
          std::for_each( 
            _functs.rbegin(), 
            _functs.rend(), 
            [&_last_msg]( std::pair<catch_msg_funct_type, IEvent::ptr>& _funct_msg )
            {
              _last_msg = _funct_msg.first( _last_msg, false );
              return;
            }
          );

          auto _src_complite = _src;
#if 0
          //Если данное сообщение является частью транзакции.
          //1. Смотрим на уже существующие транзакции, и если данная одна из них - завершаем.
          //2. Иначе, добавляем данную транзакцию в список существующих и пересылаем сообщение дальше, соответствующему модулю.
          if( current_seq_.seq_ )
          {
            current_seq_.source_ = _src;

            auto _find_it = seqs_.find( current_seq_ );
            //1->
            if( _find_it != seqs_.end() )
            {
              _src_complite = _find_it->source_;
              seqs_.erase( _find_it );
            }
            //2->
            else
            {
              seqs_.insert( current_seq_ );

              _src_complite.reset();
            }
          }
#endif
          //  Если сообщение не часть транзакции - завершаем его через источник.
          if( _src_complite )
          {
            _functs.clear();            
            _src_complite->c1omplite_msg( _last_msg, current_seq_ );
          }
          else
          {
            UASSERT( current_seq_.dest_ );
            UASSERT_SIGNAL( "failed" );
            //current_seq_.dest_->send_msg( _last_msg );
          }
        }

        if ( !_recv_msg )
        {
          std::this_thread::sleep_for ( std::chrono::milliseconds ( ms_time_sleep_ ) );
        }

      }
      while ( true );

    }
    catch ( const std::exception& _e )
    {
      EXCEPT_LOG( _e.what() );

#if 0
      if (std::string ("user abort") != std::string ( _e.what () ) )
      {
        EXCEPT_LOG( _e.what() );

        throw;
      }
#endif
    }

    return;
  }
#endif
}

}}}      // namespace libs::ilink::appl::base
