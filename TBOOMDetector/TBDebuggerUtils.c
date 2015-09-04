//
//  TBDebuggerUtils.c
//  TrailTracker
//
//  Created by Jesse Crocker on 8/31/15.
//
//

#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sysctl.h>


bool isApplicationAttachedToDebugger() {
#ifdef DEBUG
  int  mib[4];
  mib[0] = CTL_KERN;
  mib[1] = KERN_PROC;
  mib[2] = KERN_PROC_PID;
  mib[3] = getpid();
  
  struct kinfo_proc info;
  info.kp_proc.p_flag = 0;

  size_t size = sizeof(info);
  int result = sysctl(mib, sizeof(mib) / sizeof(*mib), &info, &size, NULL, 0);
  if(result == 0) {
    return ( (info.kp_proc.p_flag & P_TRACED) != 0 );
  } else {
    return false;
  }
#else
  return false;
#endif
}
