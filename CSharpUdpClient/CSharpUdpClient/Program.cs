using System;
using System.Net;
using System.Net.Sockets;

namespace CSharpUdpClient
{
    class Program
    {
        static void Main(string[] args)
        {
            if(args.Length!=3)
                return;

            var remoteIp = args[0];
            var remotePort = int.Parse(args[1]);
            var message = args[2];

            Console.WriteLine($"Remote ip:{remotePort},remotePort:{remotePort},msg:{message}");

            UdpSocket c = new UdpSocket();
            c.Client(remoteIp, remotePort);
            c.Send(message);
        }
    }
}
