/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:20:27 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/04 21:00:06 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>


int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit)
    : _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0)
{
    this->_accountIndex = _nbAccounts;
    _nbAccounts++;
    _totalAmount += initial_deposit;

    std::cout << "[" << _displayTimestamp() << "] index:" << _accountIndex
              << ";amount:" << _amount << ";created" << std::endl;
}

Account::~Account()
{
    std::cout << "[" << _displayTimestamp() << "] index:" << _accountIndex
              << ";amount:" << _amount << ";closed" << std::endl;
    _nbAccounts--;
    _totalAmount -= _amount;
}

int Account::getNbAccounts(void)
{
	return (_nbAccounts);
}

int Account::getTotalAmount(void)
{
	return (_totalAmount);
}

int Account::getNbDeposits(void)
{
	return (_totalNbDeposits);
}

int Account::getNbWithdrawals(void)
{
	return (_totalNbWithdrawals);
}

void Account::displayAccountsInfos(void)
{
    std::cout << "[" << _displayTimestamp() << "] accounts:" << _nbAccounts
              << ";total:" << _totalAmount << ";deposits:" << _totalNbDeposits
              << ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

std::string Account::_displayTimestamp(void)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timestamp[16];
    std::strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", ltm);
    return std::string(timestamp);
}

void Account::makeDeposit(int deposit)
{
    if (deposit > 0) {
        _amount += deposit;
        _nbDeposits++;
        _totalAmount += deposit;
        _totalNbDeposits++;

        std::cout << "[" << _displayTimestamp() << "] index:" << _accountIndex
                  << ";p_amount:" << _amount - deposit
                  << ";deposit:" << deposit
                  << ";amount:" << _amount
                  << ";nb_deposits:" << _nbDeposits << std::endl;
    }
}

bool Account::makeWithdrawal(int withdrawal)
{
    if (withdrawal > 0 && withdrawal <= _amount) {
        _amount -= withdrawal;
        _nbWithdrawals++;
        _totalAmount -= withdrawal;
        _totalNbWithdrawals++;

        std::cout << "[" << _displayTimestamp() << "] index:" << _accountIndex
                  << ";p_amount:" << _amount + withdrawal
                  << ";withdrawal:" << withdrawal
                  << ";amount:" << _amount
                  << ";nb_withdrawals:" << _nbWithdrawals << std::endl;

        return true;
    } else {
        std::cout << "[" << _displayTimestamp() << "] index:" << _accountIndex
                  << ";p_amount:" << _amount
                  << ";withdrawal:" << withdrawal
                  << ";refused" << std::endl;

        return false;
    }
}

int Account::checkAmount(void) const
{
    return _amount;
}

void Account::displayStatus(void) const
{
    std::cout << "[" << _displayTimestamp() << "] index:" << _accountIndex
              << ";amount:" << _amount
              << ";deposits:" << _nbDeposits
              << ";withdrawals:" << _nbWithdrawals << std::endl;
}
