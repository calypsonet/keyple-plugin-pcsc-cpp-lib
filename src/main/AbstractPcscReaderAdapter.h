/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#pragma once

#include <atomic>
#include <typeinfo>

/* Keyple Plugin Pcsc */
#include "AbstractPcscPluginAdapter.h"
#include "CardTerminal.h"
#include "PcscReader.h"

/* Keyple Core Plugin */
#include "ObservableReaderSpi.h"
#include "WaitForCardRemovalBlockingSpi.h"
#include "WaitForCardRemovalDuringProcessingSpi.h"

/* Keyple Core Util */
#include "LoggerFactory.h"

namespace keyple {
namespace plugin {
namespace pcsc {

using namespace keyple::core::plugin::spi::reader::observable;
using namespace keyple::core::plugin::spi::reader::observable::state::processing;
using namespace keyple::core::plugin::spi::reader::observable::state::removal;
using namespace keyple::core::util::cpp;
using namespace keyple::plugin::pcsc::cpp;

/**
 * (package-private) <br>
 * Abstract class for all PC/SC reader adapters.
 *
 * @since 2.0
 */
class AbstractPcscReaderAdapter
: public PcscReader,
  public ObservableReaderSpi,
  public WaitForCardRemovalDuringProcessingSpi,
  public WaitForCardRemovalBlockingSpi {
public:
    /**
     * (package-private)<br>
     * Creates an instance the class, keeps the terminal and parent plugin, extract the reader name
     * from the terminal.
     *
     * @param terminal The terminal from smartcard.io
     * @param pluginAdapter The reference to the parent plugin.
     * @since 2.0
     */
    AbstractPcscReaderAdapter(std::shared_ptr<CardTerminal> terminal, 
                              std::shared_ptr<AbstractPcscPluginAdapter> pluginAdapter);

    /**
     * 
     */
    virtual ~AbstractPcscReaderAdapter() = default;

    /**
     * (package-private)<br>
     * Gets the smartcard.io terminal.
     *
     * @return A not null reference.
     */
    virtual std::shared_ptr<CardTerminal> getTerminal() const final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual const std::string& getName() const override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual bool isProtocolSupported(const std::string& readerProtocol) const override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual void activateProtocol(const std::string& readerProtocol) override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual void deactivateProtocol(const std::string& readerProtocol) override final;

    /**
     * {@inheritDoc}
     *
     * @throws PatternSyntaxException If the expression's syntax is invalid
     * @since 2.0
     */
    virtual bool isCurrentProtocol(const std::string& readerProtocol) const override final;

    /**
     * {@inheritDoc}
     *
     * <p>The physical channel is open using the current sharing mode.
     *
     * @see #setSharingMode(SharingMode)
     * @since 2.0
     */
    virtual void openPhysicalChannel() override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual void closePhysicalChannel() override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual bool isPhysicalChannelOpen() const override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual bool checkCardPresence() override final;

    /**
     * {@inheritDoc}
     *
     * <p>In the case of a PC/SC reader, the power-on data is provided by the reader in the form of an
     * ATR ISO7816 structure whatever the card.
     *
     * @since 2.0
     */
    virtual const std::string getPowerOnData() const override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual const std::vector<uint8_t> transmitApdu(const std::vector<uint8_t>& apduCommandData)
        override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual bool isContactless() override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual void onUnregister() override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual void onStartDetection() override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual void onStopDetection() override final;

    /**
     * {@inheritDoc}
     *
     * <p>The default value is {@link SharingMode#EXCLUSIVE}.
     *
     * @since 2.0
     */
    virtual PcscReader& setSharingMode(const SharingMode sharingMode) override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual PcscReader& setContactless(const bool contactless) override final;

    /**
     * {@inheritDoc}
     *
     * <p>The default value is {@link IsoProtocol#ANY}.
     *
     * @since 2.0
     */
    virtual PcscReader& setIsoProtocol(const IsoProtocol& isoProtocol) override final;

    /**
     * {@inheritDoc}
     *
     * <p>The default value is {@link DisconnectionMode#LEAVE}.
     *
     * @since 2.0
     */
    virtual PcscReader& setDisconnectionMode(const DisconnectionMode disconnectionMode) override 
        final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual void waitForCardRemoval() override final;

    /**
     * {@inheritDoc}
     *
     * @since 2.0
     */
    virtual void stopWaitForCardRemoval() override final;

private:
    /**
     * 
     */
    const std::unique_ptr<Logger> mLogger =
        LoggerFactory::getLogger(typeid(AbstractPcscReaderAdapter));

    /**
     * 
     */
    std::shared_ptr<CardTerminal> mTerminal;

    /**
     * 
     */
    const std::string mName;

    /**
     *
     */
    std::shared_ptr<AbstractPcscPluginAdapter> mPluginAdapter;

    /**
     * 
     */
    bool mIsContactless;

    /**
     * C++ specific
     */
    bool mIsInitialized;

    /**
     * 
     */
    bool mIsPhysicalChannelOpen;

    /**
     * 
     */
    std::string mProtocol;

    /**
     * 
     */
    bool mIsModeExclusive;

    /**
     * 
     */
    DisconnectionMode mDisconnectionMode;

    /**
     * The latency delay value (in ms) determines the maximum time during which the
     * waitForCardAbsent blocking functions will execute.
     * This will correspond to the capacity to react to the interrupt signal of
     * the thread (see cancel method of the Future object)
     */
    static const long REMOVAL_LATENCY;
     
    /**
     * 
     */
    std::atomic<bool> mLoopWaitCardRemoval;

};

}
}
}
