classdef vector3D
   properties
       x;
       y;
       z;
       v;
   end
   methods
      function obj = vector3D(varargin)
         if nargin == 1
             obj.v=varargin{1};
             obj.x=obj.v(1);
             obj.y=obj.v(2);
             obj.z=obj.v(3);
         elseif nargin == 3
             obj.x=varargin{1};
             obj.y=varargin{2};
             obj.z=varargin{3};
             obj.v=[obj.x ; obj.y ; obj.z];
         end
      end
      function result = plus(obj,a)
          result = vector3D(obj.v+a.v);
      end
      function result = minus(obj,a)
          result = vector3D(obj.v-a.v);
      end 
      function obj=Rotate(obj,R)
          obj.v = R*obj.v;
          obj.x = obj.v(1);
          obj.y = obj.v(2);
          obj.z = obj.v(3);
      end
      function show(obj,n,linewidth)
          X = linspace(0,obj.x,n);
          Y = linspace(0,obj.y,n);
          Z = linspace(0,obj.z,n);
          
          zeros = linspace(0,0,n);
          axis = linspace(0,2*max(obj.v),n);
          
          plot3(axis,zeros,zeros,'linewidth',linewidth, 'color','r')
          hold on
          plot3(zeros,axis,zeros,'linewidth',linewidth, 'color', 'g')
          plot3(zeros,zeros,axis,'linewidth',linewidth, 'color','b')
          plot3(X,Y,Z, 'marker', '*')
          plot3(obj.x,obj.y,obj.z,'linewidth',linewidth)
          grid on
      end
   end
end
