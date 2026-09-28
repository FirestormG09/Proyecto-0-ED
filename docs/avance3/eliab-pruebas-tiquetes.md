# Pruebas dinámicas - Generación de tiquetes

Responsable: Eliab Moises Hernandez Lopez  
Carné: 2021032473

## Alcance

Las pruebas de esta sección verifican la generación de tiquetes del módulo
seleccionado de Proyecto-0-ED, principalmente las clases AdmSystem y Ticket.

Se comprueba la fórmula de prioridad, generación del código, consecutivo global,
validación de área, usuario y servicio, asociación entre servicio y área,
registro de la hora de creación y disponibilidad del tiquete para ser atendido.

## Framework

Se utilizó GoogleTest como framework de pruebas unitarias automatizadas.

Se seleccionó porque permite definir casos independientes, realizar aserciones
sobre los resultados y ejecutar automáticamente toda la suite desde CMake.

## Técnica de diseño

La técnica principal utilizada fue partición de equivalencia.

Las entradas fueron divididas en clases válidas e inválidas:

- Área existente / área inexistente.
- Usuario existente / usuario inexistente.
- Servicio existente / servicio inexistente.
- Servicio perteneciente al área / servicio perteneciente a otra área.

También se aplicaron valores límite al probar prioridad de usuario 0 y el
consecutivo inicial 100.

## Casos de prueba

| ID | Requisito | Riesgo | Técnica | Entrada | Resultado esperado |
|---|---|---|---|---|---|
| PT-E01 | Prioridad final | Cálculo incorrecto | Partición | Usuario=1, Servicio=2 | Prioridad 12 |
| PT-E02 | Prioridad final | Error en límite | Valor límite | Usuario=0, Servicio=2 | Prioridad 2 |
| PT-E03 | Consecutivo | Duplicación de códigos | Secuencia | Dos tiquetes | CJ100 y CJ101 |
| PT-E04 | Validar área | Ticket inválido | Partición | Área XX | No generar |
| PT-E05 | Validar usuario | Ticket inválido | Partición | Usuario inexistente | No generar |
| PT-E06 | Validar servicio | Ticket inválido | Partición | Servicio inexistente | No generar |
| PT-E07 | Servicio y área | Enrutamiento incorrecto | Partición | Servicio CJ solicitado en IN | No generar |
| PT-E08 | Hora de creación | Timestamp incorrecto | Partición | Ticket válido | Hora actual |
| PT-E09 | Cola del área | Ticket no disponible | Secuencia | Crear y atender | Se puede atender |

## Verificación

Cada prueba contiene al menos una aserción relacionada directamente con la
regla evaluada. No se considera suficiente que el código solamente se ejecute:
la prueba debe fallar si el comportamiento requerido es incorrecto.

## Resultados

Se ejecutaron 8 pruebas unitarias automatizadas mediante GoogleTest y CTest.

- 7 pruebas finalizaron correctamente.
- 1 prueba falló.
- La prueba fallida fue PT-E07: ServicioDeOtraAreaNoGeneraTicket.

Las pruebas PT-E01 a PT-E06 y PT-E08 confirmaron el comportamiento esperado
para la fórmula de prioridad, prioridad límite, consecutivo inicial,
validaciones de entradas inválidas y registro de la hora de creación.

PT-E07 reveló que el sistema permite generar un tiquete utilizando un servicio
que pertenece a un área distinta de la solicitada.

## Hallazgos dinámicos

### HD-E01 - Servicio utilizado desde un área incorrecta

**Prueba:** PT-E07 - ServicioDeOtraAreaNoGeneraTicket

**Entrada:**
- Área solicitada: IN
- Servicio: Comprar boleto
- Área registrada del servicio: CJ
- Usuario: Adulto mayor

**Resultado esperado:**  
El sistema no debe generar el tiquete porque el servicio no pertenece al área IN.

**Resultado obtenido:**  
El sistema imprimió "Tiquete generado" y creó el tiquete.

**Estado:** Confirmado.

**Severidad:** Alta.

**Conclusión:**  
La prueba dinámica confirma que no se valida la relación entre el área
seleccionada y el área asociada al servicio.