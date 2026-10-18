function corda_vibrante

   L = 1.5; %lunghezza della corda
   N = 100;
   x = linspace(0.0,L,N);
   dx = x(2)-x(1);
   dt = 0.01;

   %parametri fisici
   tens = 10; %tensione
   cq = (dx/dt)^2; %c'^2
   rho = 100+50.*x; %densità di massa
   vq = tens./rho; %c^2=(velocità di propagazione)^2=tensione/densità di massa
   a = vq./cq; %(c/c')^2
   
   t=0;
   t_end = 100;
   
   %condizione iniziale
   %u = sin((x/L)*pi);
   u = cos((x/L)*2*pi);
   u(2:N-1) = u(2:N-1)+a(2:N-1).*(u(3:N)+u(1:N-2)-2*u(2:N-1)); %u al tempo t1
   u_prev = u; %definisco u_prev per memorizzare u al tempo precedente
   while (t<t_end)
       u_now = u; %salvo u prima che venga modificato
       u(2:N-1) = 2*u(2:N-1)-u_prev(2:N-1)+a(2:N-1).*(u(3:N)+u(1:N-2)-2*u(2:N-1)); %modifico u
       u_prev = u_now; %salvo in u_prev u prima che venisse modificato

       plot(x,u);
       drawnow;

       t=t+dt;
   end
   hold off;
end