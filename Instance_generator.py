import random

class Aircraft:
  count = 1
  def __init__(self, preferred_period, periods, aircraft_type):
    self.id = aircraft_type[0] + repr(Aircraft.count)
    self.preferred = preferred_period
    self.aircraft_type = aircraft_type
    self.min = self.preferred - random.randint(10,30)
    if (self.min < 0):
      self.min = 0
    self.max = self.preferred + random.randint(30,50)
    if (self.max > periods):
       self.max = periods
    self.early_cost = random.randint(1,3)
    self.late_cost = self.early_cost * random.randint(1,3)
    Aircraft.count = Aircraft.count + 1
  def __repr__(self):
    return "%s %s %d %d %d %d %d" %(self.id, self.aircraft_type, self.min, self.preferred, self.max, self.early_cost, self.late_cost)

class Runway:
  count = 1
  def __init__(self, periods):
    self.id = "r" + repr(Runway.count)    
    Runway.count = Runway.count + 1
    self.unavailabilities_start = []
    self.unavailabilities_end = []
    if random.random() > 0.8:
      for i in range(1, random.randint(1,5)):
        unavailability_start = random.randint(0, periods)
        self.unavailabilities_start = self.unavailabilities_start + [unavailability_start]
      self.unavailabilities_start.sort()
      for i in range(0, len(self.unavailabilities_start)):
        self.unavailabilities_end = self.unavailabilities_end + [self.unavailabilities_start[i] + random.randint(10,30)]
        if self.unavailabilities_end[i] > periods:
          self.unavailabilities_end[i] = periods
      modified = True
      while modified:
        modified = False
        for i in range(0, len(self.unavailabilities_start) - 1):
          if self.unavailabilities_start[i + 1] < self.unavailabilities_end[i]:
            self.unavailabilities_start.pop(i + 1)
            self.unavailabilities_end.pop(i + 1)
            modified = True
            break
                          
  def __repr__(self):
    res = "%s %d" %(self.id, len(self.unavailabilities_start))
    for i in range(0, len(self.unavailabilities_start)):
      res += " %d %d" %(self.unavailabilities_start[i], self.unavailabilities_end[i])
    return res
    
class AircraftScheduling:
  """Problem instance for the Aircraft Scheduling Problem"""
  types = ["small", "medium", "large"]
  #def __init__(self, max_runways, max_aircrafts):
  def __init__(self, runways, aircrafts):
    #runways = random.randint(2, max_runways)
    #aircrafts = random.randint(10, max_aircrafts)

    self.periods = 120
    self.aircrafts = []
    for i in range(0,aircrafts):
      self.aircrafts = self.aircrafts + [Aircraft(random.randint(0, self.periods), self.periods, AircraftScheduling.types[random.randint(0,2)])]
    self.runways = []
    for i in range(0,runways):
      self.runways = self.runways + [Runway(self.periods)]
    self.max_landings_in_30_mins = 10
    self.sequence_delays = []
    for i in range(0,len(AircraftScheduling.types)):
      elements = []
      for j in range(0,len(AircraftScheduling.types)):
        elements.append(random.randint(2,5))
      self.sequence_delays.append(elements)
        
  def __repr__(self):
    res = ""
    res += "Aircrafts: %d\n" %(len(self.aircrafts)) 
    res += "Runways: %d\n" %(len(self.runways))
    res += "Periods: %d\n" %(self.periods)
    res += "Max_landings_in_30m: %d\n" %(self.max_landings_in_30_mins)
    res += "\nAircrafts_specification:\n"
    for a in self.aircrafts:
      res += repr(a) + "\n"
    res += "\nRunways_specification:\n"
    for r in self.runways:
      res += repr(r) + "\n"
    res += "\nSequence_delays:\n"
    for i in range(0,len(AircraftScheduling.types)):
      for j in range(0,len(AircraftScheduling.types)): 
        res += "%s %s %d\n" %(AircraftScheduling.types[i], AircraftScheduling.types[j], self.sequence_delays[i][j])
    return res


runways = 4
aircrafts = 100

import sys

if len(sys.argv) > 1:
	runways = int(sys.argv[1])
if len(sys.argv) > 2:
	aircrafts = int(sys.argv[2])

print >>sys.stderr, 'runways:', runways
print >>sys.stderr, 'aircrafts:', aircrafts

aircraft_scheduling = AircraftScheduling(runways, aircrafts)
print aircraft_scheduling
