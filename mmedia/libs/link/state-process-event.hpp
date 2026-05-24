#pragma once
/**
\file       state-process-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_link
\brief      Файл интерфейса типа для хранения состояния обработки события внутри модуля
*/

namespace libs::link
{
/// Структура для хранения всей необходимой информации, связанной с текущим обрабатываемым событием
struct StateProcessEvent {
  //  ext types
  using childs_type = std::list< syn::ISeqEvent::id_type >;

  StateProcessEvent ();
  virtual ~StateProcessEvent ();

  bool is_seq_exist () const;
  bool is_childs_exist () const;
  bool is_failed () const;
  void reset ();
  void update (syn::IEvent::ptr& msg);

  bool                    sync_event_;   //< Флаг синхронной передачи
  bool                    request_;      //< Флаг, наличие запроса
  bool                    answer_;       //< Флаг, наличие ответа
  syn::IEvent::ptr        msg_;          //< Собственно событие
  bool                    recv_seq_;     //< Флаг, событие является частью транзакции
  bool                    make_seq_;     //< Флаг, событие является частью иницированной транзакции
  syn::ISeqEvent::id_type id_seq_;       //< Опциональный идентификатор транзакции
  childs_type             childs_;       //< Связанные запросы с текущим
  bool                    failed_;       //< Флаг ошибки при обработки запроса
  std::string             error_text_;   //< Опциональная строка с сообщение об ошибке
};

std::string to_string (const StateProcessEvent& val);
}   // namespace libs::link
