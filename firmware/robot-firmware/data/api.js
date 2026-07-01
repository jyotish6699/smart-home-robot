/*
 * ------------------------------------
 * Aegis HTTP API
 * ------------------------------------
 */

export async function api(path)
{
    try
    {
        const response =
            await fetch(path,
            {
                cache: "no-store",
                keepalive: true
            });

        return response.ok;
    }
    catch(error)
    {
        console.error(
            "[API]",
            error
        );

        return false;
    }
}

export function apiFast(path)
{
    fetch(path,
    {
        cache: "no-store",
        keepalive: true
    }).catch(console.error);
}