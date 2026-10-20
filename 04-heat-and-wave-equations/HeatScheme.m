function HeatScheme
    % Parametri fisici
    eta = 0.2; k = 10; L = 5; tau = 1;
    N = 101;
    x = linspace(0.0,L,N); dx = x(2)-x(1);

    T0 = 20; deltaT = 80;
    T = ones(N,1)*T0;
    T(1) = (T0+deltaT);
    t = 0.0;
    dt = eta*dx^2/k;
    tend = 1000*dt;
    while(t<tend)
        plot(x,T);
        drawnow;
        t = t+dt;
        T_old = T;
        T(1) = T0+deltaT*exp(-t/tau);
        T(2:N-1) = T_old(2:N_1)+eta*(T_old(3:N)-2*T_old(2:N-1)+T_old(1:N-2));
    end
    hold off;
end