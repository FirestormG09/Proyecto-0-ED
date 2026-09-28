#include <gtest/gtest.h>
#include <ctime>
#include <string>

#include "AdmSystem.h"
#include "Ticket.h"

using std::string;

static void configurarSistemaBase(AdmSystem& sistema) {
    sistema.addArea("Cajas", "CJ", 4);
    sistema.addType("Adulto mayor", 1);
    sistema.addService("Comprar boleto", "CJ", 2);
}

TEST(GeneracionTiquetes, PT_E01_CalculaPrioridadFinal) {
    AdmSystem sistema;
    configurarSistemaBase(sistema);

    testing::internal::CaptureStdout();

    sistema.addTicket("CJ", "Adulto mayor", "Comprar boleto");

    string salida = testing::internal::GetCapturedStdout();

    EXPECT_NE(salida.find("CJ100"), string::npos);
    EXPECT_NE(salida.find("12"), string::npos);
}

TEST(GeneracionTiquetes, PT_E02_PrioridadUsuarioCero) {
    AdmSystem sistema;

    sistema.addArea("Cajas", "CJ", 4);
    sistema.addType("Prioritario", 0);
    sistema.addService("Comprar boleto", "CJ", 2);

    testing::internal::CaptureStdout();

    sistema.addTicket("CJ", "Prioritario", "Comprar boleto");

    string salida = testing::internal::GetCapturedStdout();

    EXPECT_NE(salida.find("2"), string::npos);
}

TEST(GeneracionTiquetes, PT_E03_ConsecutivoIniciaEn100) {
    AdmSystem sistema;
    configurarSistemaBase(sistema);

    testing::internal::CaptureStdout();

    sistema.addTicket("CJ", "Adulto mayor", "Comprar boleto");
    sistema.addTicket("CJ", "Adulto mayor", "Comprar boleto");

    string salida = testing::internal::GetCapturedStdout();

    EXPECT_NE(salida.find("CJ100"), string::npos);
    EXPECT_NE(salida.find("CJ101"), string::npos);
}

TEST(GeneracionTiquetes, PT_E04_AreaInexistenteNoGeneraTicket) {
    AdmSystem sistema;
    configurarSistemaBase(sistema);

    testing::internal::CaptureStdout();

    sistema.addTicket("XX", "Adulto mayor", "Comprar boleto");

    string salida = testing::internal::GetCapturedStdout();

    EXPECT_EQ(salida.find("Tiquete generado"), string::npos);
}

TEST(GeneracionTiquetes, PT_E05_UsuarioInexistenteNoGeneraTicket) {
    AdmSystem sistema;
    configurarSistemaBase(sistema);

    testing::internal::CaptureStdout();

    sistema.addTicket("CJ", "Usuario inexistente", "Comprar boleto");

    string salida = testing::internal::GetCapturedStdout();

    EXPECT_EQ(salida.find("Tiquete generado"), string::npos);
    EXPECT_NE(salida.find("Tipo de usuario no encontrado"), string::npos);
}

TEST(GeneracionTiquetes, PT_E06_ServicioInexistenteNoGeneraTicket) {
    AdmSystem sistema;
    configurarSistemaBase(sistema);

    testing::internal::CaptureStdout();

    sistema.addTicket("CJ", "Adulto mayor", "Servicio inexistente");

    string salida = testing::internal::GetCapturedStdout();

    EXPECT_EQ(salida.find("Tiquete generado"), string::npos);
    EXPECT_NE(salida.find("Servicio no encontrado"), string::npos);
}

TEST(GeneracionTiquetes, PT_E07_ServicioDeOtraAreaNoGeneraTicket) {
    AdmSystem sistema;

    sistema.addArea("Cajas", "CJ", 4);
    sistema.addArea("Informacion", "IN", 2);
    sistema.addType("Adulto mayor", 1);
    sistema.addService("Comprar boleto", "CJ", 2);

    testing::internal::CaptureStdout();

    sistema.addTicket("IN", "Adulto mayor", "Comprar boleto");

    string salida = testing::internal::GetCapturedStdout();

    EXPECT_EQ(salida.find("Tiquete generado"), string::npos);
}

TEST(GeneracionTiquetes, PT_E08_RegistraHoraDeCreacion) {
    time_t antes = time(nullptr);

    Ticket ticket("CJ100", 12);

    time_t despues = time(nullptr);

    EXPECT_GE(ticket.getCreation(), antes);
    EXPECT_LE(ticket.getCreation(), despues);
}

TEST(GeneracionTiquetes, PT_E09_TicketGeneradoQuedaEnColaDelArea) {
    AdmSystem sistema;
    configurarSistemaBase(sistema);

    testing::internal::CaptureStdout();

    sistema.addTicket("CJ", "Adulto mayor", "Comprar boleto");

    testing::internal::GetCapturedStdout();

    EXPECT_NO_THROW(
        sistema.attendTicket("CJ")
    );
}

TEST(GeneracionTiquetes, PT_E10_ServicioInvalidoNoModificaContadorUsuario) {
    AdmSystem sistema;
    configurarSistemaBase(sistema);

    testing::internal::CaptureStdout();

    sistema.addTicket(
        "CJ",
        "Adulto mayor",
        "Servicio inexistente"
    );

    sistema.printStatistics();

    string salida = testing::internal::GetCapturedStdout();

    EXPECT_NE(
    salida.find("Adulto mayor: 0"),
    string::npos
);
}