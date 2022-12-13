#include "AxisRunTimeHandler.h"
#include "AxisRuntimeCommandHandler.h"

AxisRuntimeCommandHandler::AxisRuntimeCommandHandler(const TSharedPtr<FAxisRuntimeWriter>& _writer) :
    m_writer{_writer}
{

}


bool AxisRuntimeCommandHandler::CalibrateNodes()
{
    uint8 cmd[] = { 0x00, 0xEF, 0xAC, 0xEF, 0xAC, 0x01, 0x00 };
    m_writer->Write(cmd, sizeof(cmd));
    return false;
}

bool AxisRuntimeCommandHandler::ZeroNodes()
{
    uint8 cmd[] = { 0x00,0xEF, 0xAC, 0xEF, 0xAC, 0x20 };
    m_writer->Write(cmd, sizeof(cmd));
    return false;
}
bool AxisRuntimeCommandHandler::ResetHub()
{
    uint8 cmd[] = { 0x01,0xE3 };
    m_writer->Write(cmd, sizeof(cmd));
    return false;
}
bool AxisRuntimeCommandHandler::VibrateNode(uint8 index, uint8 intensity, uint8 duration)
{
    uint8 cmd[] = { 0x00,0xEF, 0xAC, 0xEF, 0xAC, 0x80, index, intensity, duration };
    m_writer->Write(cmd, sizeof(cmd));
    return false;
}

bool AxisRuntimeCommandHandler::FlashNodeLED(uint8 index, uint8 red, uint8 green, uint8 blue)
{
    uint8 cmd[] = { 0x00,0xEF, 0xAC, 0xEF, 0xAC, 0x81, index, red, green, blue };
    m_writer->Write(cmd, sizeof(cmd));
    return false;
}

void AxisRuntimeCommandHandler::StartStreaming()
{
    uint8 StartStreamingCmd[] = { 0x01, 0xE0 };
    m_writer->Write(StartStreamingCmd, sizeof(StartStreamingCmd));
}

void AxisRuntimeCommandHandler::StopStreaming()
{
    uint8 StopStreamingCmd[] = { 0x01, 0xE1 };
    m_writer->Write(StopStreamingCmd, sizeof(StopStreamingCmd));
}

