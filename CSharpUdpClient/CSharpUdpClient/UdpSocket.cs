using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace CSharpUdpClient
{
    public class UdpSocket
    {
        private readonly Socket _socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        private const int bufSize = 8 * 1024;
        private readonly State _state = new State();
        private EndPoint _epFrom = new IPEndPoint(IPAddress.Any, 0);
        private AsyncCallback _recv = null;
        private bool _reveived = false;

        public class State
        {
            public byte[] Buffer = new byte[bufSize];
        }

        public void Server(string address, int port)
        {
            _socket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.ReuseAddress, true);
            _socket.Bind(new IPEndPoint(IPAddress.Parse(address), port));
            Receive();
        }

        public void Client(string address, int port)
        {
            _socket.Connect(IPAddress.Parse(address), port);
            Receive();
        }

        public void Send(string text)
        {
            byte[] data = Encoding.ASCII.GetBytes(text);

            while (!_reveived)
            {
                _socket.BeginSend(data, 0, data.Length, SocketFlags.None, (ar) =>
                {
                    State so = (State)ar.AsyncState;
                    int bytes = _socket.EndSend(ar);
                    Console.WriteLine("SEND: {0}, {1}", bytes, text);
                }, _state);

                Thread.Sleep(1000);
            }
           
        }

        private void Receive()
        {
            _socket.BeginReceiveFrom(_state.Buffer, 0, bufSize, SocketFlags.None, ref _epFrom, _recv = (ar) =>
            {
                State so = (State)ar.AsyncState;
                int bytes = _socket.EndReceiveFrom(ar, ref _epFrom);
                _socket.BeginReceiveFrom(so.Buffer, 0, bufSize, SocketFlags.None, ref _epFrom, _recv, so);
                Console.WriteLine("RECV: {0}: {1}, {2}", _epFrom.ToString(), bytes, Encoding.ASCII.GetString(so.Buffer, 0, bytes));
                _reveived = true;
            }, _state);
        }
    }
}
