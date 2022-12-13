#include "Axis_Brain.h"
#include "Axis_Mannequin.h"
#include "AxisRuntimeEventHandler.h"
#include "AxisRuntimeCommandHandler.h"

void UAxis_Brain::UpdateMannequins()
{
	//gather the data from runtime first
	m_axisRuntime->GetNodeData(m_nodeQuat, m_nodeAcceleration);
	m_playerLocationResolver.ResolveFinalPlayerPositionAndRotation(m_hubPosition, m_hubRotation, m_hubRotationRaw);

	for (size_t i = 0; i < m_mannequins.Num(); i++)
	{
		//send the data to the mannequins
		auto mannequin = 
			static_cast<UAxis_Mannequin*>(m_mannequins[i].GetComponent(m_mannequins[i].OtherActor));

		if (mannequin != nullptr)
		{
			if(mannequin->m_updatePosition)
				mannequin->UpdateHubPosition(m_hubPosition);
			if(mannequin->m_updateHubRotation)
				mannequin->UpdateHubRotation(m_hubRotationRaw, m_hubRotationOffsetRaw);
			if(mannequin->m_updateNodes)
				mannequin->UpdateNodeData(m_nodeQuat, m_nodeAcceleration);
		}
	}
}

UAxis_Brain::UAxis_Brain() :
	m_axisRuntime{nullptr},
	m_axisEventHandler{nullptr},
	m_axisCommandInterface{nullptr},
	m_playerLocationResolver{}
{
	PrimaryComponentTick.bCanEverTick = true;
	m_nodeQuat.Init({ 0,0,0,1 }, 16);
	m_nodeAcceleration.Init({ 0,0,0 }, 16);
	m_hubRotationRaw = FQuat::Identity;
	m_hubRotationOffsetRaw = FQuat::Identity;
}

UAxis_Brain::~UAxis_Brain()
{
	//Discard everything after stop playing
	if (m_axisRuntime != nullptr)
	{
		m_axisCommandInterface->StopStreaming();
		m_axisRuntime->Stop();
		m_axisRuntime = nullptr;
	}
	if (m_axisEventHandler != nullptr)
	{
		m_axisEventHandler = nullptr;
	}

	if (m_axisCommandInterface != nullptr)
	{
		m_axisCommandInterface = nullptr;
	}

}

void UAxis_Brain::InitializeOnPlay()
{
	m_axisRuntime = std::make_unique<AxisRuntimeHandler>();
	m_axisRuntime->InitConnection();
	m_axisRuntime->Start();


	m_axisCommandInterface = std::make_unique<AxisRuntimeCommandHandler>(m_axisRuntime->GetRuntimeWriter());
	m_axisCommandInterface->StartStreaming();

	const auto& runtimeReader = m_axisRuntime->GetRuntimeReader();
	const auto& runtimeWriter = m_axisRuntime->GetRuntimeWriter();

	m_playerLocationResolver.InitListeners(m_francisListener, runtimeReader->GetHubReader());

	m_axisEventHandler = std::make_unique<AxisRuntimeEventHandler>(runtimeReader,runtimeWriter);
}


void UAxis_Brain::BeginPlay()
{
	Super::BeginPlay();
	InitializeOnPlay();
}

void UAxis_Brain::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateMannequins();
}

void UAxis_Brain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	
}


FQuat UAxis_Brain::GetNodeQuatData(const EAxisPartEnum& _axisNode)
{
	return m_nodeQuat[_axisNode];
}

FVector UAxis_Brain::GetNodeAccelerationData(const EAxisPartEnum& _axisNode)
{
	return m_nodeAcceleration[_axisNode];
}


FVector UAxis_Brain::GetHubPosition()
{
	return m_hubPosition;
}

FQuat UAxis_Brain::GetHubRotation()
{
	return m_hubRotationRaw;
}
bool UAxis_Brain::IsESPConnected(EEventEnum& _eventEnum, const float _timeout)
{
	return m_axisEventHandler ? m_axisEventHandler->IsESPConnected(_timeout) : false;
}

bool UAxis_Brain::IsHubConnected(EEventEnum& _eventEnum, const float _timeout)
{
	return m_axisEventHandler ? m_axisEventHandler->IsHubConnected(_timeout) : false;
}

bool UAxis_Brain::IsRuntimeConnected(EEventEnum& _eventEnum, const float _timeout)
{
	return m_axisEventHandler ? m_axisEventHandler->IsRuntimeConnected(_timeout) : false;
}

bool UAxis_Brain::CalibrateNodes()
{
	return m_axisCommandInterface ? m_axisCommandInterface->CalibrateNodes() : false;
}

bool UAxis_Brain::ZeroNodes()
{
	return m_axisCommandInterface ? m_axisCommandInterface->ZeroNodes() : false;
}

bool UAxis_Brain::ResetHub()
{
	return m_axisCommandInterface ? m_axisCommandInterface->ResetHub() : false;
}

