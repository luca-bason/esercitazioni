function HeatSchemeAsym
    % Parametri fisici
    eta = 0.2; L = 0.5; kappa = 10; % Delta x, Delta t
    N = 101; x = linspace(0.0,L,N);
    dx = x(2)-x(1); dt = (eta*dx^2)/kappa; % Impulso di calore iniziale
    T0     = 20; DeltaT = 80;
    T      = ones(N,1)*T0;
    T(1:2) = T(1:2) + DeltaT;
    % Evoluzione
    t = 0; tend = 1e-3; 
    k = 0;
    time = zeros(N,1);
    temp = zeros(N,1);
    while t<tend
       % Metodo esplicito
       T(N)     = T0;
       T(1)     = T(1) + 2*eta*(T(2)-T(1));
       T(2:N-1) = T(2:N-1) + eta*(T(3:N)+T(1:N-2)-2*T(2:N-1));
       plot(x,T);
       % Salvataggio t e T (per un punto della sbarra) e loro disegno
       time(end+1) = t;
       temp(end+1) = T(3);
       % plot(time,temp);
       drawnow; % cercare parametri per rendere piu' o meno lenta la visualizzazione
       t = t+dt;
    end
    hold off;
end
