#include "../subghz_i.h"
#include "../helpers/subghz_custom_event.h"

void subghz_scene_show_only_rx_popup_callback(void* context) {
    SubGhz* subghz = context;
    view_dispatcher_send_custom_event(subghz->view_dispatcher, SubGhzCustomEventSceneShowOnlyRX);
}

void subghz_scene_show_only_rx_on_enter(void* context) {
    SubGhz* subghz = context;

    // Setup view
    Popup* popup = subghz->popup;

    const char* header_text = "Transmision bloqueada";
    const char* message_text = "Transmitir en\nesta frecuncia\nesta restringido";
    if(!furi_hal_region_is_provisioned()) {
        header_text = "Actualizacion requerida";
        message_text = "Actualiza\nantes de usar\nesta funcion\nflipp.dev/upd";
    }

    popup_set_header(popup, header_text, 63, 3, AlignCenter, AlignTop);
    popup_set_text(popup, message_text, 0, 17, AlignLeft, AlignTop);
    popup_set_icon(popup, 72, 17, &I_DolphinCommon_56x48);

    popup_set_timeout(popup, 1500);
    popup_set_context(popup, subghz);
    popup_set_callback(popup, subghz_scene_show_only_rx_popup_callback);
    popup_enable_timeout(popup);
    view_dispatcher_switch_to_view(subghz->view_dispatcher, SubGhzViewIdPopup);
}

bool subghz_scene_show_only_rx_on_event(void* context, SceneManagerEvent event) {
    SubGhz* subghz = context;
    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubGhzCustomEventSceneShowOnlyRX) {
            scene_manager_previous_scene(subghz->scene_manager);
            return true;
        }
    }
    return false;
}

void subghz_scene_show_only_rx_on_exit(void* context) {
    SubGhz* subghz = context;
    Popup* popup = subghz->popup;

    popup_reset(popup);
}
