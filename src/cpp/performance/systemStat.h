/*
This file is part of KUNKUN.

Foobar is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.


<systemStat.h>
<this class is used for get system stat info on Linux system>

Author: Zheng Li
*/

#ifndef SYSTEM_STAT_H
#define SYSTEM_STAT_H

class SystemStat {
 public:
  // The return value is n%.
  int getCPUUsage();

};

#endif
