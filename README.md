# Proyecto-0-ED

## TIPOS DE USUARIO
- "adulto mayor","persona con encesidades especiales","usuario regular","representante organizacional".
- Tiene que tener descripcion y un numero que representa la prioridad a ser atendido, entre menor el numero mayor la priorirdad
- El sistema maneja una lista de tipos de usuarios ordenados segun su prioridad
- por la consulta de estadisticas: tener un contador de tiquetes por cada tipo de usuario.

## SERVICIO
- "comprar boleto", "cambiar boleto", "solicitar informacion", "realizar reclamo" 
- Tiene que tener una descripcion y un numero que representa la prioridad del servicio y el area donde se atienede
- ordenada segun se quiera configurar.
- por la consulta de estadisticas: contador de tiquete por cada servicio disponible.

## AREAS
- secciones donde se atienden los servicios
- el sistema las configura con descripcion, codigo: string que las identifica, y una serie de ventanillas que posee el area
- una cola de prioridad con los tiquetes
- no puede tener una lista de servicios. tiene que jalar de la lista ya existente de servicios.
  
  - ## VENTANILLAS
una lista de pares que asocia el nombre de la ventanilla con el nombre del ticket
  - nombre que es el codigo concatenado con un consecutivo. ejemplo C como nombre y 4 ventanillas entonces c1 c2 c3 c4
  - Tiene que tener un espacio para mostrar el codigo del tiquete que se atiende
  - por consulta de estadisticas: contador de cantidad de tiquetes atendidos para cada ventanilla
  - por la consulta de estadisticas: tener un contador de tiquetes atendidos

## TIQUETE  
- codigo: codigo del area y un consecutivo global, consecutivo empieza en 100. NUNCA se genera uno con un diferente numero de area y mismo consecutivo
- Hora en que fueron solicitados, tiempo de espera para ser atendidos se calcula luego.
- Prioridad final: PrioridadTiquete = PrioridadUsuario * 10 + PrioridadServicio

# FUNCIONALIDADES DEL SISTEMA
## Solicitud de un tiquete
- selecciona tipo de usuario
- servicio a usar
- genera tiquete con el codigo
- hora actual
- prioridad final 
- se inserta en la cola prioridad del area

## Ventanilla atiene tiquete
- ingresa el codigo de la ventanilla que atiende el tiquete
- extrae tiquete de la cola prioridad del area al que pertenece ventanilla
- actualiza el codigo del tiquete siendo atendido
- registra la hora en que fue atendido.

## Administracion del sistema
- agregar o eliminar elementos de listas de tipos de usuario, areas disponibles, ventanillas y servicios disponibles.
- Si se borra un tipo de usuario o servicio se eliminan todos los tiquetes.
- Si se borra un area se eliminan todos los servicios y las ventanillas
- Dar un mensaje de advertencia y solicitar confirmacion antes de borrar.

## Consulta de estadisticas
- Tiempo promedio de espera por cada area
  - llevar control del tiempo que toma a cada tiquete en ser atendido y cantidad de tiquetes atendidos en un area.
- Cantidad de tiquetes dispensados por area
  - control de esa info
- Cantidad de tiquetes atendidos por ventanilla
  - para cada ventanilla en especifico
- Cantidad de tiquetes solicitados por servicio
  - para cada servicio en especifico
- Cantidad de tiquetes emitidos por cada tipo de usuario

# ESTRUCTURA SUGERIDA PARA MENU
siempre mostrar las opciones al usuario y cada opcion debe de ser de facil interaccion.
- ## 1. Estado de las colas
   - Muestra areas existentes
   - Cantidad de ventanillas por cada area
   - Codigos de los tiquetes presentes en las colas
   - Cada ventanilla muestra el codigo del ultimo tiquete atendido.
   - opcion para regresar al menu principal
- ## 2. Tiquetes
   - Seleccionar tipo de cliente
     - Muestra la lista de tipos de usuarios para escojer uno sin mostrar las prioridades. Usuario selecciona el tipo de cliente que es
   - Seleccionar tipo de servicio
     - Muestra la lista de servicios, el orden de esta lista no debe ser fija ni por areas, se configura en el sistema.
     - Usuario seleciona un servicio y el sistema genera el tiquete y lo inserta en la cola de prioridad respectiva
     - Imprime todos los datos del tiquete
     - Se mantiene en el menu de tiquetes al hacer esta accion
   - Regresar a menu
- ## 3. Atender
  - Solicita al usuario area y numero de ventanilla
  - busca en la cola respectiva el siguiente en ser atendido, lo elimina de la cola y lo asigna como tiquete que se esta atendiendo.
  - Actualiza los datos necesario para que se refleje en las estadisticas.
  - Si no hay ningun elemento en la cola debe indicar que no hay usuarios en espera, luego de realizar la accion regresa al menu principal.
- ## 4. Administracion
  - ### Tipos de usuario
    - Agregar
      - agrega un tipo de usuario con su nombre y prioridad a la lista de tipos de usuario del sistema, ordena la lista segun priordad.
      - Luego de realizar la accion se mantiene en el menu de tipos de usuario.
    - Eliminar
      - Elimina un tipo de usuario del sistema. luego de realizar la accion se mantiene en el menu de tipos de usuario.
    - Regresar
      - regresa al menu de administracion
  - ### Areas
    - Agregar
      - Agrega una nueva area con su respectiva desccripcion, codigo y cantidad de ventanillas y la agreaga a la lista de areas del sistema.
      - Crea automaticamente la lista de ventanillas con sus codigos
      - Luego de la accion se mantiene en el menu de areas
    - Modificar cantidad de ventanillas.
      - Se solicita un area existente dentro del sistema, muestra la cantidad de ventanillas actuales y solicita un nuevo numero de ventanillas.
      - Borra las anteriores "clear" y las crea denuevo segun la solicitud del usuario.
      - Se mantiene en el menu areas luego de hacer la accion
    - Eliminar
      - Elimina un area y todas sus ventanillas asociadas. Si hay servicios relacionados con el area que se boora, tambien se eliminan
      - Se muestra la lista de servicios que desaparecerian si se borra el area.
      - Tambien debe pedirse confirmacion al usuario antes de hacerlo.
      - Se mantiene en el menu areas luego de hacer la accion
  - ### Servicios disponibles
    - Agregar
      - agrega un nuevo servicio con su descripcion, area de atencion y prioridad
      - se mantiene en el menu de servicios disponibles luego de hacer la accion
    - Eliminar
      - Muestra la lista de servicios disponibles y elige uno para eliminarlo
      - Deben borrarse todos los tiquetes de las cosas de todas las areas.
      - Luego de realizar la accion se mantiene en el menu de servicios disponinbles.
    - Reordenar
      - Permite al usuario reordenar los elementos en la lista de servicios. Solicita el numero de servicio a reubicar y la posicion destino.
      - Solo hay una lista de servicios y no se debe de aprupar por area ni por otro criterio.
      - Luego de realizar la accion se mantiene en el menu de servicios disponibles.
    - Regresar
      - regresa al menu de administracion.
 - ### Limpiar cola y estadisticas
   - Limpiar cola y estadisticas
     - Elimina los contenidos de todas las colas de prioridad, los tiquetes atendidos en ventanillas y los datos de las estadisticas registrados hasta el momento.
     - Es un reinicio del sistema que no afecta tipos de usuario, servicios ni areas
     - Luego de hacer la accion vuelve al menu de administracion
   - Regresar
     - regresa al menu principal sin realizar ninguna accion
- ### Estadisticas del sistema
  - Se muestran todas las estadisticas explicadas anteriormente de una forma clara y concisa.
  - Se espera a que el usario presione alguna tecla para regresar al menu principal.
- ### Salir
  - Abandonar el programa
# POSTDATA
Gente, revisé la clase donde el profe explica todo y no estoy seguro si hay que cambiar algo en nuestros planes:
- Un area puede atender muchos servicios, cada servicio es atendidio en un area, entonces un area puede tener una lista de servicios que hace, es necesario que la lista se pueda reordenar.
- Un area tiene una cantidad de ventanillas (personalizable) donde la cola de prioridad de area se va a atender.
- Hay que cambiar la hora a la que se pide un tiquete a time o calendar (o lo que haya en C++)

# Avance 2 - Pruebas estáticas

## Resumen semanal

Durante esta semana se realizaron las pruebas estáticas del proyecto Proyecto-0-ED.
Se documentaron cuatro Inspections formales y cuatro revisiones adicionales.
También se configuraron y ejecutaron cuatro herramientas de análisis estático.
Los resultados fueron revisados manualmente para distinguir hallazgos reales de advertencias.
Finalmente, se documentaron los defectos encontrados sin modificar el código original.

## Commits del avance

Commit inicial: XXXXXXX  
Commit final: XXXXXXX  

Rango de commits:

XXXXXXX..XXXXXXX