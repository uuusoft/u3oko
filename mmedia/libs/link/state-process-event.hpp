#pragma once
/**
\file       state-process-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_link
\brief      Файл интерфейса типа для хранения состояния обработки события внутри модуля
*/

namespace libs::link
{
/// Структура для хранения всей необходимой информации, связанной с текущим обрабатываемым событием
struct StateProcessEvent {
  //  ext types
  using childs_type = std::list< syn::ISeqEvent::id_type >;

  StateProcessEvent ()          = default;
  virtual ~StateProcessEvent () = default;

  auto is_seq_exist () const -> bool;
  auto is_childs_exist () const -> bool;
  auto is_failed () const -> bool;
  auto reset () -> void;
  auto update (syn::IEvent::ptr&) -> void;

  bool                    sync_event_ = false;   //< Флаг синхронной передачи
  bool                    request_    = false;   //< Флаг, наличие запроса
  bool                    answer_     = false;   //< Флаг, наличие ответа
  syn::IEvent::ptr        msg_        = {};      //< Собственно событие
  bool                    recv_seq_   = false;   //< Флаг, событие является частью транзакции
  bool                    make_seq_   = false;   //< Флаг, событие является частью иницированной транзакции
  syn::ISeqEvent::id_type id_seq_     = {};      //< Опциональный идентификатор транзакции
  childs_type             childs_     = {};      //< Связанные запросы с текущим
  bool                    failed_     = false;   //< Флаг ошибки при обработки запроса
  std::string             error_text_ = {};      //< Опциональная строка с сообщение об ошибке
};

std::string to_string (const StateProcessEvent& val);
}   // namespace libs::link
