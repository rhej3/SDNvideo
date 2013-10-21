"""
SDN-based application for efficient video streaming- Internet2 Innovative Application award 2013
Aditi Ghag
Rasha El-Jaroudi
"""

import httplib
import json

import sys,getopt



class StaticFlowPusher(object):

    def __init__(self, server):
        self.server = server

    def get(self, data):
        ret = self.rest_call({}, 'GET')
        return json.loads(ret[2])

    def set(self, data):
        ret = self.rest_call(data, 'POST')
        return ret[0] == 200

    def remove(self, objtype, data):
        ret = self.rest_call(data, 'DELETE')
        return ret[0] == 200

    def rest_call(self, data, action):
        path = '/wm/staticflowentrypusher/json'
        headers = {
            'Content-type': 'application/json',
            'Accept': 'application/json',
            }
        body = json.dumps(data)
        conn = httplib.HTTPConnection(self.server, 8080)
        conn.request(action, path, body, headers)
        response = conn.getresponse()
        ret = (response.status, response.reason, response.read())
        print ret
        conn.close()
        return ret
          

def main(argv):
  
  if len(sys.argv) < 2:
    print 'Enter controller IP address'
    sys.exit()
   

if __name__ == "__main__":
   main(sys.argv[1:])

pusher = StaticFlowPusher(str(sys.argv[1]))

#Add flow to Los Angeles switch at port 63
flow1 = {
    
'switch':"00:01:34:40:b5:09:7c:00",
"name":"flow-mod-1",
"cookie":"0",
"priority":"32768",
"ingress-port":"63",
"active":"true",
"actions":"output=flood"
  }

#Add flow to Los Angeles switch at port 17
flow4 = {
'switch':"00:01:34:40:b5:09:7c:00",
"name":"flow-mod-4",
"cookie":"0",
"priority":"32768",
"ingress-port":"17",
"active":"true",
"actions":"output=flood"
}

#Add flow to Raleigh switch at port 17
flow2 = {
   
'switch':"00:01:34:40:b5:03:11:00",
"name":"flow-mod-2",
"cookie":"0",
"priority":"32768",
"ingress-port":"17",
"active":"true",
"actions":"output=flood"
    }
#Add flow to Raleigh switch at port 63
flow3 = {
'switch':"00:01:34:40:b5:03:11:00",
"name":"flow-mod-3",
"cookie":"0",
"priority":"32768",
"ingress-port":"63",
"active":"true",
"actions":"output=flood"
}

#Add flow to Raleigh switch at port 18
flow5 = {
'switch':"00:01:34:40:b5:03:11:00",
"name":"flow-mod-5",
"cookie":"0",
"priority":"32768",
"ingress-port":"18",
"active":"true",
"actions":"output=flood"
}

#Add flow to Washington DC switch at port 18
flow6 = {
'switch':"00:01:34:40:b5:03:17:00",
"name":"flow-mod-6",
"cookie":"0",
"priority":"32768",
"ingress-port":"18",
"active":"true",
"actions":"output=flood"
}

#Add flow to Washington DC switch at port 17
flow7 = {
'switch':"00:01:34:40:b5:03:17:00",
"name":"flow-mod-7",
"cookie":"0",
"priority":"32768",
"ingress-port":"17",
"active":"true",
"actions":"output=flood"
}

"""
flow8 = {
'switch':"00:01:34:40:b5:03:21:00",
"name":"flow-mod-8",
"cookie":"0",
"priority":"32768",
"ingress-port":"17",
"active":"true",
"actions":"output=flood"
}

flow9 = {
'switch':"00:01:34:40:b5:03:21:00",
"name":"flow-mod-9",
"cookie":"0",
"priority":"32768",
"ingress-port":"18",
"active":"true",
"actions":"output=flood"
}

"""
#Add flow to Seattle switch at port 17
flow8 = {
'switch':"00:01:34:40:b5:09:a1:00",
"name":"flow-mod-8",
"cookie":"0",
"priority":"32768",
"ingress-port":"17",
"active":"true",
"actions":"output=flood"
}

#Add flow to Seattle switch at port 18
flow9 = {
'switch':"00:01:34:40:b5:09:a1:00",
"name":"flow-mod-9",
"cookie":"0",
"priority":"32768",
"ingress-port":"18",
"active":"true",
"actions":"output=flood"
}

#Add flow to Los Angeles switch at port 18
flow13 = {
'switch':"00:01:34:40:b5:09:7c:00",
"name":"flow-mod-13",
"cookie":"0",
"priority":"32768",
"ingress-port":"18",
"active":"true",
"actions":"output=flood"
}
#Add flow to Chicago switch at port 18
flow10 = {
'switch':"00:01:34:40:b5:03:06:00",
"name":"flow-mod-10",
"cookie":"0",
"priority":"32768",
"ingress-port":"18",
"active":"true",
"actions":"output=flood"
}

#Add flow to Chicago switch at port 63
flow11 = {
'switch':"00:01:34:40:b5:03:06:00",
"name":"flow-mod-11",
"cookie":"0",
"priority":"32768",
"ingress-port":"63",
"active":"true",
"actions":"output=flood"
}

#Add flow to Washington DC switch at port 63
flow12 = {
'switch':"00:01:34:40:b5:03:17:00",
"name":"flow-mod-12",
"cookie":"0",
"priority":"32768",
"ingress-port":"63",
"active":"true",
"actions":"output=flood"
}

"""
pusher.remove(json,flow1)
pusher.remove(json,flow2)
pusher.remove(json,flow3)
pusher.remove(json,flow4)
pusher.remove(json,flow5)
pusher.remove(json,flow6)
pusher.remove(json,flow7)
pusher.remove(json,flow8)
pusher.remove(json,flow9)
pusher.remove(json,flow10)
pusher.remove(json,flow11)
pusher.remove(json,flow12)
pusher.remove(json,flow13)
"""
pusher.set(flow1)
pusher.set(flow2)
pusher.set(flow3)
pusher.set(flow4)
pusher.set(flow5)
pusher.set(flow6)
pusher.set(flow7)
pusher.set(flow8)
pusher.set(flow9)
pusher.set(flow10)
pusher.set(flow11)
pusher.set(flow12)
pusher.set(flow13)

