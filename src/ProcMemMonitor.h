/* -*- Mode: C++; tab-width: 8; c-basic-offset: 2; indent-tabs-mode: nil; -*- */

#ifndef RR_PROC_MEM_MONITOR_H_
#define RR_PROC_MEM_MONITOR_H_

#include "FileMonitor.h"
#include "TaskishUid.h"

namespace rr {

/**
 * A FileMonitor to track writes to /proc/<pid>/mem so they can be replayed
 * when <pid> is a replayed tracee.
 */
class ProcMemMonitor : public FileMonitor {
public:
  ProcMemMonitor(Task* t, const std::string& pathname);

  virtual Type type() { return ProcMem; }

  /**
   * During replay, copy writes to tracee |tid|'s memory.
   */
  virtual void did_write(Task* t, const std::vector<Range>& ranges,
                         int64_t offset);

private:
  // 0 if this doesn't object doesn't refer to a tracee's proc-mem.
  TaskUid tuid;
};

} // namespace rr

#endif /* RR_PROC_MEM_MONITOR_H_ */
