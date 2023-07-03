#include <stddef.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE	4096LU
#endif

inline static void	__update_buff(
	char *const buff,
	char const *const ptr,
	size_t *const buff_size)
{
// We must copy the right number of bytes from the given pointer `ptr`
// to the given pointer `buff`. This is a way to erase the first characters
// that are contained in the buffer. We must also update the buffer size,
// reducing it by the number of erased characters
// (or setting it to the number of copied characters).
}

inline static int	__append_buff_to_line(
	char *const buff,
	char **const line,
	size_t *const buff_size,
	size_t *const line_size)
{
// In a first time, we must determine whether the buffer contains a newline.
//
// If it does contain a newline, then
// |
// |  If `line` is not allocated yet, then
// |  |
// |  |  We must allocate enough memory to contain
// |  |  the characters that are preceding the found newline in the buffer,
// |  |  and an additional ending null character.
// |  |
// |  |  If the allocation fails, then
// |  |  |
// |  |  |  We must return a status indicating that an error occured.
// |  |  |
// |  |  End
// |  |
// |  |  Then we must copy the characters that are preceding the found newline
// |  |  in the buffer to the newly allocated line,
// |  |  and add an ending null character to it.
// |  |
// |  |  Then we must update the buffer content, erasing the copied characters
// |  |  and the found newline. We must update the buffer size accordingly.
// |  |  To do this, let's call another function named `__update_buff`
// |  |
// |  |  Finally, we must return a status indicating that the line can be returned.
// |  |
// |  End
// |
// |  We must allocate enough memory to contain
// |  the characters that are currently present in the line,
// |  the characters that are preceding the found newline in the buffer,
// |  and an additional ending null character.
// |
// |  If the allocation fails, then
// |  |
// |  |  We must return a status indicating that an error occured.
// |  |
// |  End
// |
// |  Then we must copy the characters that are currently present in the line,
// |  the characters that are preceding the foung newline in the buffer,
// |  and an ending null character to the newly allocated area.
// |  We must also set this newly allocated area as being the new line.
// |
// |  Then we must update the buffer content, erasing the copied characters
// |  and the found newline. We must update the buffer size accordingly.
// |  To do this, let's call another function named `__update_buff`
// |
// |  Finally, we must return a status indicating that the line can be returned.
// |
// End
//
// If `line` is not allocated yet, then
// |
// |  We must allocate enough memory to contain the whole content of the buffer.
// |
// |  If the allocation fails, then
// |  |
// |  |  We must return a status indicating that an error occured.
// |  |
// |  End
// |
// |  Then we must copy the whole content of the buffer
// |  to the newly allocated line. We must also update the line size accordingly.
// |
// |  Finally, we must return a status indicating that we need to call `read` again.
// |
// End
//
// We must allocate enough memory to contain
// the characters that are currently present in the line
// and the whole content of the buffer.
//
// If the allocation fails, then
// |
// |  We must return a status indicating that an error occured.
// |
// End
//
// Then we must copy the characters that are currently present in the line,
// and the whole content of the buffer to the newly allocated area.
// We must also set the newly allocated area as being the new line.
// We must also update the line size accordingly.
//
// Finally, we must return a status indicating that we need to call `read` again.
}

char	*get_next_line(int const fd)
{
	static char		buff[BUFFER_SIZE] = {0};
	static size_t	buff_size = 0LU; // This represents the number of non-garbage bytes that are in the buffer at any given time.
	size_t			line_size = 0LU;
	char			*line = NULL;
	ssize_t			read_ret;

// In a first time, if the static buffer contains something,
// we must put it to the current line.
// [!] This does not mean to naively put the entire content of the buffer.
// [!] Supposing that the buffer actually contains, for example
// [!] {'a', 'b', '\n', 'c', '\n', 'd', 'e', '\n'}
// [!] (note that there is voluntarily no null character at the end)
// [!] Then, we must put only {'a', 'b'} to the line.
// To do this, let's call another function named `__append_buff_to_line`

// While we are needing to read more from the given file descriptor
// |
// |  We must call the `read` function, using the buffer to store the read data.
// |
// |  If the reading failed, then
// |  |
// |  |  We must return a NULL pointer (beware the memory leaks)
// |  |
// |  End
// |
// |  Then, we must set the buffer size to the number of characters actually read.
// |  Then, we must put the content of the buffer to the current line.
// |  To do this, let's call another function named `__append_buff_to_line`
// |
// End
//
// If an error occured, then
// |
// |  We must return a NULL pointer (beware the memory leaks)
// |
// End
//
// Finally, we must return the current line.
}
