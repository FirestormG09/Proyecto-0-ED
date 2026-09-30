#include <gtest/gtest.h>
#include <stdexcept>

#include "Area.h"
#include "Counter.h"
#include "Ticket.h"

TEST(AtencionAreas, PT_P01_ColaVaciaLanzaError) {
    Area area("Caja", "CJ", 1);

    EXPECT_THROW(area.attendNextTicket(), std::runtime_error);
}

TEST(AtencionAreas, PT_P02_AgregarYAtenderTicket) {
    Area area("Caja", "CJ", 1);
    Ticket ticket("CJ100", 12);

    area.addTicket(ticket);

    Ticket atendido = area.attendNextTicket();

    EXPECT_EQ(atendido.getCode(), "CJ100");
    EXPECT_EQ(atendido.getFinalPriority(), 12);
}

TEST(AtencionAreas, PT_P03_AtiendeMayorPrioridadPrimero) {
    Area area("Caja", "CJ", 1);

    Ticket ticket1("CJ100", 22);
    Ticket ticket2("CJ101", 3);

    area.addTicket(ticket1);
    area.addTicket(ticket2);

    Ticket atendido = area.attendNextTicket();

    EXPECT_EQ(atendido.getCode(), "CJ101");
    EXPECT_EQ(atendido.getFinalPriority(), 3);
}

TEST(AtencionAreas, PT_P04_PromedioInicialEsCero) {
    Area area("Caja", "CJ", 1);

    EXPECT_FLOAT_EQ(area.averageWaitTime(), 0.0f);
}

TEST(AtencionAreas, PT_P05_InicializaCantidadDeVentanillas) {
    Area area("Caja", "CJ", 2);

    EXPECT_EQ(area.getNumCounter(), 2);
    EXPECT_EQ(area.getCounters().getSize(), 2);

    area.getCounters().goToPos(0);
    EXPECT_EQ(area.getCounters().getElement().getName(), "CJ1");

    area.getCounters().goToPos(1);
    EXPECT_EQ(area.getCounters().getElement().getName(), "CJ2");
}

TEST(Ventanillas, PT_P06_AsignaTicketAVentanillaLibre) {
    Counter counter("CJ1");
    Ticket ticket("CJ100", 12);

    bool asignado = counter.assignTicket(ticket);

    EXPECT_TRUE(asignado);
    EXPECT_EQ(counter.currentTicket.getCode(), "CJ100");
    EXPECT_EQ(counter.getTicketsServed(), 1);
}

TEST(Ventanillas, PT_P07_RechazaTicketSiEstaOcupada) {
    Counter counter("CJ1");

    Ticket ticket1("CJ100", 12);
    Ticket ticket2("CJ101", 15);

    EXPECT_TRUE(counter.assignTicket(ticket1));
    EXPECT_FALSE(counter.assignTicket(ticket2));

    EXPECT_EQ(counter.currentTicket.getCode(), "CJ100");
    EXPECT_EQ(counter.getTicketsServed(), 1);
}

TEST(Ventanillas, PT_P08_PermiteOtroTicketDespuesDeLiberar) {
    Counter counter("CJ1");

    Ticket ticket1("CJ100", 12);
    Ticket ticket2("CJ101", 15);

    EXPECT_TRUE(counter.assignTicket(ticket1));

    counter.clearCurrentTicket();

    EXPECT_TRUE(counter.assignTicket(ticket2));
    EXPECT_EQ(counter.currentTicket.getCode(), "CJ101");
    EXPECT_EQ(counter.getTicketsServed(), 2);
}