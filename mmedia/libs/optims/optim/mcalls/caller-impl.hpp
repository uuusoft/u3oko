#pragma once
/**
\file       caller-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_optim_lib
*/

namespace libs::optim::mcalls
{
/// Класс реализует вызов параллельный вызов кода в нескольких потоках
class CallerImpl final : public IMCaller
{
  public:
  //  ext types
  using statistic_work_func_type = std::function< bool (syn::ExpandedTimes& obj) >;

  CallerImpl ();
  virtual ~CallerImpl ();
  CallerImpl (const CallerImpl&)            = delete;
  CallerImpl& operator= (const CallerImpl&) = delete;

  // IMCaller
  virtual void          set_count_threads (std::uint16_t) override;
  virtual std::uint16_t get_count_threads () const override;
  virtual void          mthreads_call (const ::libs::core::graph::NodeID&, const MTFuncInfo&, ::libs::optim::io::MCallInfo&, syn::ExpandedTimes&, const std::uint16_t) override;

  // EAI-REFACT to private
  void thread_func_impl (const std::uint32_t);
  void thread_postfunc_impl (std::uint32_t);

  private:
  //  internal typess
  using sync_type        = std::mutex;
  using lock_type        = std::scoped_lock< sync_type >;
  using funcs_mcall_type = std::vector< io::mtcall_func >;

  void stop_and_wait_threads ();
  void create_threads ();
  void mthreads_call_int (const MTFuncInfo& funct, ::libs::optim::io::MCallInfo& info, std::uint16_t athreads);

  static std::atomic< std::uint32_t > impl_counter_;   //<

  MTFuncSharedInfo             sinfo_;          //< Разделяемая информция между всеми потоками
  std::uint16_t                max_threads_;    //< Максимальное количество потоков, которое можно будет использовать
  std::vector< std::thread >   threads_;        //< Рабочие потоки
  std::vector< io::MCallInfo > calls_;          //< Не разделяемая информация вызова для каждого потока
  std::vector< std::uint32_t > src_heights_;    //< Высоты всех источников всех потоков, т.к. для каждого потока возможно уникальное деление по высоте
  funcs_mcall_type             thread_funcs_;   //< Рабочие функции потоков, т.е. фактически алгоритмы обработоки данных
  mutable sync_type            mtx_;            //< Синронизирующий примитив для упорядочивания доступа к объекту
};

// U3-REFACT
/// Функция эвристика, возвращает количество рабочих потоков на основе количества ядер процессора
unsigned long get_count_work_threads_by_count_cpu (unsigned long);
}   // namespace libs::optim::mcalls
