#include "earth_mars.pb-c.h"

int send_from_mars(FromMars *from_mars, int connected_socket)
{
    uint32_t msg_size;
    size_t nb_bytes;
    uint8_t *buf;
    int rc = 0;

    /* alloc and fill buf */
    msg_size = from_mars__get_packed_size(from_mars);
    buf = malloc(msg_size);
    if (!buf) {
        fprintf(stderr, "Captain unable to alloc buf to send from_mars.\n");
        return ENOMEM;
    }

    nb_bytes = from_mars__pack(from_mars, buf);
    if (nb_bytes != (size_t)msg_size) {
        fprintf(stderr,
                "Captain error when packing from_mars: %u instead of %u .\n",
               nb_bytes, msg_size);
        rc = ENOMEM;
    }

    rc = send_protobuf(connected_socket, buf, msg_size);
    if (rc) {
        fprintf(stderr,
                "Captain error on sending from_mars: %d, %s .\n",
                rc, strerror(rc));
    }

/* protobuf variables */

    Astronaut captain, crew_member;
    RescueDemand rescue_demand;
    FromEarth *from_earth;
    FromMars from_mars;
    Date ask_before;
    uint8_t *buf = NULL;
    size_t buf_size;
    int rc;



/* prepare rescue_demand */
    date__init(&ask_before);
    ask_before.year = 2032;
    ask_before.month = 11;
    ask_before.day = 27;
    astronaut__init(&captain);
    captain.name = "Captain";
    captain.health_status = ASTRONAUT__HEALTH_STATUS__AILING;
    astronaut__init(&crew_member);
    crew_member.name = "Gary";
    captain.health_status = ASTRONAUT__HEALTH_STATUS__GOOD;
    rescue_demand__init(&rescue_demand);
    rescue_demand.id = 1;
    rescue_demand.ask_before = &ask_before;
    rescue_demand.n_astronaut = 2;
    rescue_demand.astronaut = malloc(sizeof(Astronaut *) * 2);

/* send rescue_demand */
    rc = send_from_mars(&from_mars, connected_socket);

/* recv from_earth buf */
    rc = recv_protobuf(connected_socket, &buf, &buf_size);

/* unpack data */
    from_earth = from_earth__unpack(NULL, buf_size, buf);

