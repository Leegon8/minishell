# Minishell

Este proyecto consiste en recrear una versión simplificada del funcionamiento de la terminal y el lenguaje de bash.<br>
<h2>👽Space🛸shell team members</h2>

<div align="center">
  
<table>
  <tr>
    <td align="center" width="400">Lauriane González</td>
    <td align="center" width="400">Luis Prieto</td>
  </tr>
  <tr>
    <td align="center" width="400"><img width="150" src="https://github.com/user-attachments/assets/56c69eeb-005d-48fd-b0b5-8ff97d3dc170" /></td>
    <td align="center" width="400"><img width="150" src="https://github.com/LLuisPP/ONCE-scalian/assets/116104082/18bf3bbf-ec5f-489b-82e6-ca878ecdde1d" /></td>
  </tr>
    <td align="center" width="400">Desarrolladora</td>
    <td align="center" width="400">Desarrollador</td>
  </tr>
  <tr>
    <td align="center" width="400">42 login: lauriago</td>
    <td align="center" width="400">42 login: lprieto-</td>
  </tr>
</table>

</div>

# Descriptión and requirements

<h3 weight="bold">The proyect consists in develop a bash shell like program.</h3>

- It must be written using <b>C</b> and had to be compiled with <b>Makefile</b>.
  - Shell has to behave as original GNU shell, and it can't crash.

<em>Requirements</em> table:

<div align="center">
<table>
  <tr>
    <td align="center" width="130">Language</td>
    <td align="center">Builtins</td>
    <td align="center" width="700">Functions allowed</td>
  </tr>
  <tr>
    <td align="center"><img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="c" width="70" height="70"/><br><br><br><img src="https://github.com/user-attachments/assets/bd668d04-50d1-496a-beb6-2190b1fe9241" alt="makefile" width="50" height="60"/><br>Makefile<br>
    </td>
    <td align="center" width="100">• echo <br><br> • cd <br><br> • pwd <br><br> • export <br><br> • unset <br><br> • env <br><br> • exit <br> </td>
    <td width="330">
      <br>
      • readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay <br><br>
      • add_history, printf, malloc, free, write, access, open, read, close, fork<br><br>
      • wait, waitpid, wait3, wait4signal, sigaction, sigemptyset, sigaddset, kill<br><br>
      • exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe<br><br>
      • opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot<br><br>
      • ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum<br><br>
      • tgetstr, tgoto, tputs<br><br>
      <br>
      </td>
  </tr>
</table>
</div>
<br>

<h3 weight="bold">Basic workflow chart for a comand:</h3>

<img align="center" src="https://github.com/user-attachments/assets/d1577d14-d5cb-4d15-a416-b1d55b44ad54"></img>


# Organization

<h3 weight="bold">Task schedule distribution</h3>

<div align="center">

<table>
  <tr>
    <th>Week</th>
    <th>Member 🅰️</th>
    <th>Member 🅱️</th>
    <th>📍 Milestones 📅</th>
  </tr>
  <tr>
    <td align="center">1</td>
    <td>- Estructs ✅<br>- Bucle in con readline ✅<br>- Configurar entorno ❌</td>
    <td>- Estudiar señales ⭕<br>- Gestión de señales ⭕<br>- Escribir tests básicos ⭕</td>
    <td>Milestone 1:<br>- Entrada de comando ✅<br>- Manejo simple señales ⭕</td>
  </tr>
  <tr>
    <td align="center">2</td>
    <td>- Entrada con tokenizer ❌<br>- Implementar tokenizador ⭕<br>- Tests tokenizador ❌</td>
    <td>- Documentar data y funct ❌<br>- Implementar parser ⭕<br>- Tests para parser ⭕</td>
    <td>Milestone 2:<br>- Tokenización y parsing ❌<br>- Integración inicial ❌</td>
  </tr>
  <tr>
    <td align="center">3</td>
    <td>- Implementar built ins ⭕<br>- Gestionar add_history ✅<br>- Tests history / builts ❌</td>
    <td>- Exec cmds externos ❌<br>- Manejar errores básicos ⭕<br>- Tests history / builts ❌</td>
    <td>Milestone 3:<br>- Cmds int y ext ❌<br>- Historial funcional ✅</td>
  </tr>
  <tr>
    <td align="center">4</td>
    <td>- Redirects E/S (`>`, `<`) ❌<br>- Redirect errors ❌<br>- Documentar data y funct ❌</td>
    <td>- Exec cmds ext con pipes ❌<br>- Tests pipes ❌<br>- Opt memoria leaks-frees ❌</td>
    <td>Milestone 4:<br>- Redirect pipes y funct ❌</td>
  </tr>
  <tr>
    <td align="center">5</td>
    <td>- Manejo advanced señales ❌<br>- Env vars getenv ❌<br>- Tests env/signs/funct ❌</td>
    <td>- Code optimize leak-free ❌<br>- Error handling strerror ❌<br>- Error handle p/strerror ❌</td>
    <td>Milestone 5:<br>- Advcd sig, vars env ❌<br>- Código optimizado ❌</td>
  </tr>
  <tr>
    <td align="center">6</td>
    <td>- Integrar funcionalidades<br>- Pruebas exhaustivas<br>- Documentar proyecto final</td>
    <td>- Rendimiento y optimización<br>- Verificar Makefile y exec</td>
    <td>Milestone 6:<br>- testeado y document<br>- norminette, norma</td>
  </tr>
</table>

</div>
