/*
 * Copyright (c) 2011 Aeroflex Gaisler
 *
 * BSD license:
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include <asm-leon/queue.h>
/*#include <sys/fsu_pthread_queue.h>*/
#include <asm-leon/contextswitch.h>
#include <asm-leon/leonbare_kernel.h>
#include <asm-leon/leonbare_debug.h>
#include <asm-leon/stack.h>
#include <asm-leon/leonstack.h>
#include <asm-leon/irq.h>

int
leonbare_thread_getqueueidx (leonbare_thread_t thread)
{
  LEONBARE_VERIFYSCHED ();
  if (thread->th_flags & (LEONBARE_TH_TERMINATED | LEONBARE_TH_FINISHED))
    {
      return LEONBARE_RUNQ_KILLED_IDX;
    }
  else if ((thread->th_flags & LEONBARE_TH_SUSPENDED))
    {
      return LEONBARE_RUNQ_SUSPENDED_IDX;
    }
  else if (LEONBARE_RUNQ_ISREADY (thread->th_runq_idx))
    {
      if (LEONBARE_KR_RUNQ_WHICH == thread->th_runq_which)
	{
	  return thread->th_runq_idx;
	}
      else
	{
	  return thread->th_runq_idx + LEONBARE_RUNQ_PREPARE_IDX;
	}
    }
  return -1;
}
