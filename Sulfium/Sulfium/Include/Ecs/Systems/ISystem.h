#pragma once

namespace SFM
{
	/// <summary>
	/// ESystem stage defines the flow of the engine.
	/// Each stage represent a batch of systems that should be able to run concurrently.
	/// </summary>
	enum class ESystemStage
	{
		PreFrame,
		OnLoad,
		PostLoad,
		PreUpdate,
		OnUpdate,
		PostUpdate,
		OnStore,
		PostStore,
		PostFrame,
		STAGE_MAX
	};

	/// <summary>
	/// The interface specified for the systems used in Sulfium.
	/// </summary>
	class ISystem
	{
	public:
		ISystem(bool enabled = true, ESystemStage stage = ESystemStage::PostUpdate);
		virtual ~ISystem() = default;

		ISystem(const ISystem& rhs) = delete;
		ISystem(ISystem&& rhs) = default;

		virtual void Execute(float dt) = 0;

		unsigned int GetId() const;
		bool IsEnabled() const;
		ESystemStage GetStage() const;

	private:
		unsigned int m_id;
		bool m_enabled;
		ESystemStage m_stage;
	
		static int s_systemCount;
	};
}