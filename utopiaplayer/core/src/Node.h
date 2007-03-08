/******************************************************************************\
*  Utopia Player - A cross-platform, multilingual, tagging media manager       *
*  Copyright (C) 2006-2007 John Eric Martin <john.eric.martin@gmail.com>       *
*                                                                              *
*  This program is free software; you can redistribute it and/or modify        *
*  it under the terms of the GNU General Public License version 2 as           *
*  published by the Free Software Foundation.                                  *
*                                                                              *
*  This program is distributed in the hope that it will be useful,             *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of              *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
*  GNU General Public License for more details.                                *
*                                                                              *
*  You should have received a copy of the GNU General Public License           *
*  along with this program; if not, write to the                               *
*  Free Software Foundation, Inc.,                                             *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                   *
\******************************************************************************/

#ifndef __Node_h__
#define __Node_h__

#include <QtCore/QList>
#include <QtCore/QQueue>
#include <QtCore/QVariant>

typedef enum _NodeType
{
	Source = 0,
	Filter,
	Destination
}NodeType;

typedef enum _PacketType
{
	Sound,
	Meta,
	Flush
}PacketType;

typedef struct _Packet
{
	PacketType type;
	void *data;
}Packet;

typedef struct _SoundPacket
{
	int rate; // The sample rate of the data
	int channels; // The number of channels (normally 2)
	int count; // The ammount of samples

	// The sound samples. To use you would go:
	// float *left = samples[0];
	// float *right = samples[1];
	// left[i] *= 1; right[i] *= 1;
	float **samples;
}SoundPacket;

class Node
{
public:
	Node(int input_count, int output_count, int channels);
	virtual ~Node();

	void setInput(int port, Node *node, int nodePort);
	void setOutput(int port, Node *node, int nodePort);

	QList<Node*> inputs() const;
	QList<Node*> outputs() const;

	Node* input(int port) const;
	Node* output(int port) const;

	// Sends sound samples to this node
	virtual int input(float **samples, int count);
	// Recieves sound samples from this node
	virtual int output(float **samples, int count);

	int inputCount();
	int outputCount();

	virtual NodeType type() = 0;

	static void glue(Node *node1, int node1port, Node *node2, int node2port);
	static void unglue(Node *node1, int node1port, Node *node2, int node2port);

	QMap<QString, QVariant> getOptions() const;
	QVariant getOption(const QString& optionName) const;

	void setOption(const QString& optionName, const QVariant& option);

	virtual void reset();

protected:
	//void buffer(int size);

	int mChannels;
	QQueue<float*> mBuffer;

	QList<int> mInputPorts;
	QList<int> mOutputPorts;

	QList<Node*> mInputNodes;
	QList<Node*> mOutputNodes;

	QMap<QString, QVariant> mOptions;
};

#endif // __Node_h__
