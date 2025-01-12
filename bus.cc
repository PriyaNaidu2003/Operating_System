#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"

using namespace ns3;
NS_LOG_COMPONENT_DEFINE("SecondScriptExample");
int main(int argc,char *argv[])
{
LogComponentEnable("UdpEchoClientApplication",LOG_LEVEL_INFO);
LogComponentEnable("UdpEchoServerApplication",LOG_LEVEL_INFO);
NodeContainer p2pNodes;
p2pNodes.Create(2);
NodeContainer csmaNodes;
csmaNodes.Add(p2pNodes.Get(1));
csmaNodes.Create(3);
PointToPointHelper pointToPoint;
pointToPoint.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
pointToPoint.SetChannelAttribute("Delay",StringValue("2ms"));
NetDeviceContainer p2pDevices;
p2pDevices=pointToPoint.Install(p2pNodes);
CsmaHelper csma;
csma.SetChannelAttribute("DataRate",StringValue("100Mbps"));
csma.SetChannelAttribute("Delay",TimeValue(NanoSeconds(6560)));

NetDeviceContainer csmaDevices;
csmaDevices=csma.Install(csmaNodes);
InternetStackHelper Stack;
Stack.Install(p2pNodes.Get(0));
Stack.Install(csmaNodes);
Ipv4AddressHelper address;
address.SetBase("10.1.1.0","255.255.255.0");
Ipv4InterfaceContainer p2pInterface;
p2pInterface=address.Assign(p2pDevices);
address.SetBase("10.2.1.0","255.255.255.0");
Ipv4InterfaceContainer csmaInterface;
csmaInterface=address.Assign(csmaDevices);
UdpEchoServerHelper echoServer(9);
ApplicationContainer ServerApps=echoServer.Install(csmaNodes.Get(3));
ServerApps.Start(Seconds(1.0));
ServerApps.Stop(Seconds(10.0));
UdpEchoClientHelper echoClient(csmaInterface.GetAddress(3),9);
echoClient.SetAttribute("MaxPackets",UintegerValue(1));
echoClient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
echoClient.SetAttribute("PacketSize",UintegerValue(1024));
ApplicationContainer ClientApps=echoClient.Install(p2pNodes.Get(0));
ClientApps.Start(Seconds(2.0));
ClientApps.Stop(Seconds(10.0));
Ipv4GlobalRoutingHelper :: PopulateRoutingTables();
pointToPoint.EnablePcapAll("p2p");
csma.EnablePcapAll("csma");
AnimationInterface anim("bus.xml");
anim.SetConstantPosition(p2pNodes.Get(0),10.0,10.0);
anim.SetConstantPosition(csmaNodes.Get(0),20.0,20.0);
anim.SetConstantPosition(csmaNodes.Get(1),30.0,30.0);
anim.SetConstantPosition(csmaNodes.Get(2),40.0,40.0);
anim.SetConstantPosition(csmaNodes.Get(3),50.0,50.0);
Simulator::Run();
Simulator::Destroy();
return 0;
}
