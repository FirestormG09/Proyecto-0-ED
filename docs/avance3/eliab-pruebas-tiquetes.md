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

## Matriz de casos de prueba

| ID | Requisito | Riesgo | Técnica | Entrada | Resultado esperado |
|---|---|---|---|---|---|
| PT-E01 | Calcular prioridad | Prioridad incorrecta | Partición | Usuario=1, Servicio=2 | Prioridad 12 |
| PT-E02 | Prioridad mínima | Error de límite | Valor límite | Usuario=0, Servicio=2 | Prioridad 2 |
| PT-E03 | Consecutivo | Códigos duplicados | Secuencia | Dos tiquetes | CJ100 y CJ101 |
| PT-E04 | Validar área | Ticket inválido | Partición | Área XX | No genera |
| PT-E05 | Validar usuario | Ticket inválido | Partición | Usuario inexistente | No genera |
| PT-E06 | Validar servicio | Ticket inválido | Partición | Servicio inexistente | No genera |
| PT-E07 | Validar área del servicio | Enrutamiento incorrecto | Partición | Servicio CJ solicitado en IN | No genera |
| PT-E08 | Registrar creación | Hora incorrecta | Partición | Ticket válido | Hora actual |
| PT-E09 | Insertar en cola del área | Ticket perdido | Secuencia | Generar y atender | Puede atenderse |
| PT-E10 | Mantener contador | Estadística incorrecta | Partición | Servicio inexistente | Contador permanece en 0 |


## Verificación

Cada prueba contiene al menos una aserción relacionada directamente con la
regla evaluada. No se considera suficiente que el código solamente se ejecute:
la prueba debe fallar si el comportamiento requerido es incorrecto.

## Resultados de ejecución

Se ejecutaron 10 pruebas unitarias automatizadas mediante GoogleTest y CTest.

- 7 pruebas finalizaron correctamente.
- 3 pruebas detectaron comportamientos distintos de los esperados.
- PT-E07 detectó que se puede generar un tiquete usando un servicio perteneciente a otra área.
- PT-E09 detectó que el tiquete generado no queda disponible en la cola del área correspondiente.
- PT-E10 detectó que el contador del usuario se modifica aunque el servicio solicitado no exista.

Los tres fallos se consideran hallazgos del producto y no errores de la suite,
ya que las aserciones representan el comportamiento esperado del sistema.

| ID | Resultado | Observación |
|---|---|---|
| PT-E01 | PASS | La prioridad se calculó correctamente |
| PT-E02 | PASS | Se aceptó correctamente la prioridad mínima probada |
| PT-E03 | PASS | Se generaron los consecutivos CJ100 y CJ101 |
| PT-E04 | PASS | No se generó un tiquete con un área inexistente |
| PT-E05 | PASS | No se generó un tiquete con un usuario inexistente |
| PT-E06 | PASS | No se generó un tiquete con un servicio inexistente |
| PT-E07 | FAIL | Se generó un tiquete utilizando un servicio perteneciente a otra área |
| PT-E08 | PASS | La hora de creación quedó dentro del intervalo esperado |
| PT-E09 | FAIL | El tiquete generado no quedó disponible en la cola del área |
| PT-E10 | FAIL | El contador del usuario cambió aunque el servicio solicitado no existía |


## Hallazgos dinámicos

### HD-E01 - Servicio utilizado desde un área incorrecta

**Prueba:** PT-E07  
**Esperado:** No generar el tiquete.  
**Obtenido:** El sistema generó el tiquete.  
**Severidad:** Alta.  
**Estado:** Confirmado.

El sistema no valida que el servicio seleccionado pertenezca al área desde la
cual se solicita el tiquete.

### HD-E02 - Tiquete generado no se inserta en la cola del área

**Prueba:** PT-E09  
**Esperado:** Después de generar un tiquete para CJ, este debe poder atenderse
desde dicha área.  
**Obtenido:** Se lanzó std::runtime_error con el mensaje
"No hay tiquetes en espera.".  
**Severidad:** Alta.  
**Estado:** Confirmado.

El tiquete se registra en el sistema, pero no queda disponible en la cola de
prioridad del área correspondiente.

### HD-E03 - El contador del usuario aumenta aunque no se genere el tiquete

**Prueba relacionada:** PT-E10  
**Resultado esperado:** Cuando el servicio solicitado no existe, no debe generarse el tiquete y el contador del tipo de usuario debe permanecer en 0.  
**Resultado obtenido:** La salida de estadísticas no mostró `Adulto mayor: 0`. Durante la verificación diagnóstica previa se comprobó que el contador había quedado en 1.  
**Estado:** Confirmado.  
**Severidad propuesta:** Media.

El contador del tipo de usuario se modifica antes de completar la validación del servicio. Como consecuencia, las estadísticas pueden registrar un tiquete que nunca llegó a generarse.

## Cobertura

La cobertura fue medida utilizando LLVM Coverage 22.1.3 mediante
instrumentación del ejecutable de pruebas.

Para evitar que el framework de pruebas alterara los resultados, se excluyeron
del reporte los archivos pertenecientes a GoogleTest y el propio archivo
test_tickets.cpp.

La suite desarrollada alcanzó aproximadamente:

- Cobertura de funciones: 48.13 %
- Cobertura de líneas: 42.70 %
- Cobertura de ramas: 34.21 %
- Cobertura de regiones: 43.45 %

Los porcentajes no representan la cantidad de pruebas aprobadas, sino la
proporción del código del proyecto que fue ejecutada durante las pruebas.

La cobertura no alcanza el 100 % debido a que esta sección se concentró en el
flujo de generación de tiquetes. Funciones relacionadas con administración,
estructuras auxiliares, ventanillas, atención completa y otras operaciones del
sistema quedan fuera del alcance de estas pruebas específicas.

Entre los archivos principales, AdmSystem.h obtuvo 43.68 % de cobertura de
líneas y 78.95 % de ramas, Area.h obtuvo 65.04 % de líneas y 75 % de ramas,
mientras Ticket.h alcanzó 71.43 % de cobertura de líneas.

## Cierre de la parte asignada

La suite automatizada cubre entradas válidas e inválidas del flujo de generación de tiquetes mediante partición de equivalencia, valores límite y secuencias de estado.

Se confirmaron dinámicamente tres defectos:

1. Falta de validación entre servicio y área.
2. El tiquete generado no se inserta en la cola del área.
3. El contador del usuario aumenta aunque la generación falle por un servicio inexistente.

Los resultados quedaron respaldados por la salida de CTest y por el reporte de cobertura generado con LLVM Coverage.