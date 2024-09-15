# Minishell

Este proyecto consiste en recrear una versión simplificada del funcionamiento de la terminal y el lenguaje de bash.<br>
<h2>👽Space🛸shell team members</h2>

<div align="center">
  
<table>
  <tr>
    <td align="center" width="500">Lauriane González</td>
    <td align="center" width="500">Luis Prieto</td>
  </tr>
  <tr>
    <td align="center" width="500"><img width="150" src="https://github.com/user-attachments/assets/56c69eeb-005d-48fd-b0b5-8ff97d3dc170" /></td>
    <td align="center" width="500"><img width="150" src="https://github.com/LLuisPP/ONCE-scalian/assets/116104082/18bf3bbf-ec5f-489b-82e6-ca878ecdde1d" /></td>
  </tr>
    <td align="center" width="500">Desarrolladora</td>
    <td align="center" width="500">Desarrollador</td>
  </tr>
  <tr>
    <td align="center" width="500">42 login: lauriago</td>
    <td align="center" width="500">42 login: lprieto-</td>
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
    <td align="center"><br><img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="c" width="70" height="70"/><br><br><br><img src="https://github.com/user-attachments/assets/bd668d04-50d1-496a-beb6-2190b1fe9241" alt="makefile" width="50" height="60"/><br>Makefile<br>
    </td>
    <td align="center" width="120">• echo <br><br> • cd <br><br> • pwd <br><br> • export <br><br> • unset <br><br> • env <br><br> • exit <br> </td>
    <td width="330">
      <br>
      • readline • rl_clear_history • rl_on_new_line • rl_replace_line • rl_redisplay • add_history <br><br>
      • printf, malloc, free, write, access, open • read, close, fork, wait, waitpid, wait3, wait4 <br><br>
      • signal, sigaction, sigemptyset, sigaddset, kill • exit, getcwd, chdir, stat, lstat <br><br>
      • fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir • strerror, perror <br><br>
      • isatty, ttyname, ttyslot • ioctl, getenv, tcsetattr, tcgetattr, tgetent<br><br>
      • tgetflag, tgetnum, tgetstr, tgoto, tputs<br><br><br>
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


```
+------------+------------------------------+------------------------------+-----------------------------+
|   Semana   |          Member 🅰           |           Member 🅱          |       📍 Milestones  📅     |
+------------+------------------------------+------------------------------+-----------------------------+
|            | - Estructs                ✅ | - Estudiar señales        ⭕ | Milestone 1:                |
|  Week  1️⃣  | - Bucle in con readline   ✅ | - Gestión de señales      ⭕ | - Entrada de comando     ✅ |
|            | - Configurar entorno      ❌ | - Escribir tests básicos  ⭕ | - manejo simple señales  ⭕ |
+------------+------------------------------+------------------------------+-----------------------------+
|            | - Implementar tokenizador ⭕ | - Implementar parser      ⭕ | Milestone 2:                |
|  Week  2️⃣  | - Tests tokenizador       ❌ | - Tests para parser       ⭕ | - Tokenización y parsing ❌ |
|            | - Entrada con tokenizer   ❌ | - Documentar data y funct ❌ | - Integración inicial    ❌ |
+------------+------------------------------+------------------------------+-----------------------------+
|            | - Implementar built ins   ⭕ | - Exec cmds externos      ❌ | Milestone 3:                |
|  Week  3️⃣  | - Gestionar add_history   ✅ | - Manejar errores básicos ⭕ | - Cmds int y ext         ❌ |
|            | - Tests history / builts  ❌ | - Tests history / builts  ❌ | - Historial funcional    ✅ |
+------------+------------------------------+------------------------------+-----------------------------+
|            | - Redirects E/S (`>`, `<`)❌ | - Exec cmds ext con pipes ❌ | Milestone 4:                |
|  Week  4️⃣  | - Redirect errors         ❌ | - Tests pipes             ❌ | - Redirect pipes y funct ❌ |
|            | - Documentar data y funct ❌ | - Opt memoria leaks-frees ❌ |                             |
+------------+------------------------------+------------------------------+-----------------------------+
|            | - Manejo advanced señales ❌ | - Code optimize leak-free ❌ | Milestone 5:                |
|  Week  5️⃣  | - Env vars getenv         ❌ | - Error handling strerror ❌ | - Advcd sig, vars env    ❌ |
|            | - Tests env/signs/funct   ❌ | - Error handle p/strerror ❌ | - Código optimizado      ❌ |
+------------+------------------------------+------------------------------+-----------------------------+
|            | - Integrar funcionalidades   | - Rendimiento y optimización | Milestone 6:                |
|  Week  6️⃣  | - Pruebas exhaustivas        | - Verificar Makefile y       | - testeado y document       |
|            | - Documentar proyecto final  | - Verificar Makefile y exec  | - norminette, norma,        |
+------------+------------------------------+------------------------------+-----------------------------+
```
