// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VT_COVERGROUP_NEGATIVE_RANGES_H_
#define VERILATED_VT_COVERGROUP_NEGATIVE_RANGES_H_  // guard

#include "verilated.h"

class Vt_covergroup_negative_ranges__Syms;
class Vt_covergroup_negative_ranges___024root;
class Vt_covergroup_negative_ranges_std;
class Vt_covergroup_negative_ranges_std__03a__03aprocess__Vclpkg;
class Vt_covergroup_negative_ranges_std__03a__03asemaphore__Vclpkg;
class Vt_covergroup_negative_ranges_t;
class Vt_covergroup_negative_ranges_t__03a__03acg__Vclpkg;


// This class is the main interface to the Verilated model
class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_negative_ranges VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vt_covergroup_negative_ranges__Syms* const vlSymsp;

  public:

    // CONSTEXPR CAPABILITIES
    // Verilated with --trace?
    static constexpr bool traceCapable = false;

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&clk,0,0);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.
    Vt_covergroup_negative_ranges_t* const __PVT__t;
    Vt_covergroup_negative_ranges_std* const __PVT__std;
    Vt_covergroup_negative_ranges_t__03a__03acg__Vclpkg* const t__03a__03acg__Vclpkg;
    Vt_covergroup_negative_ranges_std__03a__03asemaphore__Vclpkg* const std__03a__03asemaphore__Vclpkg;
    Vt_covergroup_negative_ranges_std__03a__03aprocess__Vclpkg* const std__03a__03aprocess__Vclpkg;

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vt_covergroup_negative_ranges___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vt_covergroup_negative_ranges(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vt_covergroup_negative_ranges(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vt_covergroup_negative_ranges();
  private:
    VL_UNCOPYABLE(Vt_covergroup_negative_ranges);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Are there scheduled events to handle?
    bool eventsPending();
    /// Returns time at next time slot. Aborts if !eventsPending()
    uint64_t nextTimeSlot();
    /// Trace signals in the model; called by application code
    void trace(VerilatedTraceBaseC* tfp, int levels, int options = 0) { contextp()->trace(tfp, levels, options); }
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
    /// Prepare for cloning the model at the process level (e.g. fork in Linux)
    /// Release necessary resources. Called before cloning.
    void prepareClone() const;
    /// Re-init after cloning the model at the process level (e.g. fork in Linux)
    /// Re-allocate necessary resources. Called after cloning.
    void atClone() const;
  private:
    // Internal functions - trace registration
    void traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options);
};

#endif  // guard
