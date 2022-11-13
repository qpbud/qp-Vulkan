#include "commandPool/CommandPoolCommon.hpp"

namespace bud::vk {

void CommandPoolCommon::Entry::trimCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags) {
    auto& commandPoolCommonInternal = static_cast<CommandPoolCommon&>(*commandPool);
    commandPoolCommonInternal.trim(flags);
}

VkResult CommandPoolCommon::Entry::resetCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolResetFlags flags) {
    auto& commandPoolCommonInternal = static_cast<CommandPoolCommon&>(*commandPool);
    commandPoolCommonInternal.reset(flags);
    return VK_SUCCESS;
}

void CommandPoolCommon::Entry::destroyCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    const VkAllocationCallbacks* pAllocator) {
    if (commandPool != VK_NULL_HANDLE) {
        auto& commandPoolCommonInternal = static_cast<CommandPoolCommon&>(*commandPool);
        Allocator allocator = commandPoolCommonInternal.getAllocator();
        allocator.destruct(commandPoolCommonInternal);
    }
}

CommandPoolCommon::CommandPoolCommon(
    DeviceCommon& deviceCommon,
    const VkCommandPoolCreateInfo& commandPoolCreateInfo,
    const Allocator& allocator)
    : Object<VkCommandPool_T>(allocator)
    , m_deviceCommon(deviceCommon)
    , m_flags(commandPoolCreateInfo.flags)
    , m_queueFamilyIndex(commandPoolCreateInfo.queueFamilyIndex) {}

}
