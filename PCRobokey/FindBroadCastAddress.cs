using System.Net.NetworkInformation;
using System.Diagnostics;
using System.Collections.Generic;

namespace Robokey
{
    class FindBroadcastAddreses
    {
        public static string[] Find()
        {
            var addresses = new List<string>();
            NetworkInterface[] nis = NetworkInterface.GetAllNetworkInterfaces();
            foreach (var ni in nis)
            {
                if (ni.OperationalStatus == OperationalStatus.Up
                    && ni.NetworkInterfaceType != NetworkInterfaceType.Loopback
                    && ni.NetworkInterfaceType != NetworkInterfaceType.Tunnel)
                {
                    var ips = ni.GetIPProperties();
                    if (ips != null)
                    {
                        foreach (var uip in ips.UnicastAddresses)
                        {
                            var mask = uip.IPv4Mask.GetAddressBytes();
                            if (mask[0] != 0 || mask[1] != 0 || mask[2] != 0 || mask[3] != 0)
                            {
                                var adr = uip.Address.GetAddressBytes();
                                for (int i = 0; i < adr.Length; ++i)
                                {
                                    adr[i] = (byte)(adr[i] | ~mask[i]);
                                }
                                string adrStr = "" + adr[0] + "." + adr[1] + "." + adr[2] + "." + adr[3];
                                addresses.Add(adrStr);
                                Debug.WriteLine("ip: " + uip.Address + "mask: " + uip.IPv4Mask + "adr:" + adrStr);
                            }
                        }
                    }
                }
            }
            return addresses.ToArray();
        }
    };
}
