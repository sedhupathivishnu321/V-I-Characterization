classdef ArduinoDataPlotter < matlab.apps.AppBase

    % Properties that correspond to app components
    properties (Access = private)
        UIFigure            matlab.ui.Figure
        StartButton         matlab.ui.control.Button
        StopButton          matlab.ui.control.Button
        SaveImageButton     matlab.ui.control.Button
        SaveCSVButton       matlab.ui.control.Button
        PortDropDownLabel   matlab.ui.control.Label
        PortDropDown        matlab.ui.control.DropDown
        BaudRateDropDownLabel  matlab.ui.control.Label
        BaudRateDropDown    matlab.ui.control.DropDown
        UIAxes              matlab.ui.control.UIAxes
        PortList            cell
        SerialPort  
        Time            
        VoltageData      
        CurrentData        
    end

    % App initialization and construction
    methods (Access = private)

        %UIFigure and components
        function createComponents(app)
            %UIFigure
            app.UIFigure = uifigure;
            app.UIFigure.Position = [100 100 800 600];
            app.UIFigure.Name = 'Arduino Data Plotter';
            app.UIFigure.CloseRequestFcn = createCallbackFcn(app, @appCloseRequest, true);

            %StartButton
            app.StartButton = uibutton(app.UIFigure, 'push');
            app.StartButton.ButtonPushedFcn = createCallbackFcn(app, @startButtonPushed, true);
            app.StartButton.Position = [30 500 100 22];
            app.StartButton.Text = 'Start';

            % StopButton
            app.StopButton = uibutton(app.UIFigure, 'push');
            app.StopButton.ButtonPushedFcn = createCallbackFcn(app, @stopButtonPushed, true);
            app.StopButton.Position = [150 500 100 22];
            app.StopButton.Text = 'Stop';

            % SaveImageButton
            app.SaveImageButton = uibutton(app.UIFigure, 'push');
            app.SaveImageButton.ButtonPushedFcn = createCallbackFcn(app, @saveImageButtonPushed, true);
            app.SaveImageButton.Position = [270 500 120 22];
            app.SaveImageButton.Text = 'Save Image';

            %  SaveCSVButton
            app.SaveCSVButton = uibutton(app.UIFigure, 'push');
            app.SaveCSVButton.ButtonPushedFcn = createCallbackFcn(app, @saveCSVButtonPushed, true);
            app.SaveCSVButton.Position = [410 500 100 22];
            app.SaveCSVButton.Text = 'Save CSV';

            % PortDropDownLabel
            app.PortDropDownLabel = uilabel(app.UIFigure);
            app.PortDropDownLabel.HorizontalAlignment = 'right';
            app.PortDropDownLabel.Position = [30 540 28 22];
            app.PortDropDownLabel.Text = 'Port';

            % PortDropDown
            app.PortDropDown = uidropdown(app.UIFigure);
            app.PortDropDown.Items = {'Select Port'};
            app.PortDropDown.Position = [73 540 100 22];

            % BaudRateDropDownLabel
            app.BaudRateDropDownLabel = uilabel(app.UIFigure);
            app.BaudRateDropDownLabel.HorizontalAlignment = 'right';
            app.BaudRateDropDownLabel.Position = [200 540 60 22];
            app.BaudRateDropDownLabel.Text = 'Baud Rate';

            %  BaudRateDropDown
            app.BaudRateDropDown = uidropdown(app.UIFigure);
            app.BaudRateDropDown.Items = {'9600', '115200'}; % Add more options if needed
            app.BaudRateDropDown.Position = [270 540 100 22];
            app.BaudRateDropDown.Value = '9600';

            % Create UI
            app.UIAxes = uiaxes(app.UIFigure);
            title(app.UIAxes, 'Voltage vs. Current')
            xlabel(app.UIAxes, 'Time (s)')
            ylabel(app.UIAxes, 'Value')
            app.UIAxes.Position = [30 30 740 450];
        end
    end

    
    methods (Access = public)

        % Construct app
        function app = ArduinoDataPlotter
     
            createComponents(app)

            ports = serialportlist("available");
            if ~isempty(ports)
                app.PortList = cellstr(ports); 
                app.PortDropDown.Items = ports;
            else
                app.PortDropDown.Items = {'No ports available'};
                app.StartButton.Enable = 'off';
            end
        end
        function delete(app)
           
            if ~isempty(app.SerialPort) && isvalid(app.SerialPort) && strcmp(app.SerialPort.Status, 'open')
                fclose(app.SerialPort);
                delete(app.SerialPort);
            end
        end
    end

    methods (Access = private)

       
        function startButtonPushed(app, ~)
            try
                %  port and baud rate 
                selectedPort = app.PortDropDown.Value;
                selectedBaudRate = str2double(app.BaudRateDropDown.Value);
                app.SerialPort = serialport(selectedPort, selectedBaudRate);
                configureTerminator(app.SerialPort, "LF");

                % Initialize data arrays
                app.Time = [];
                app.VoltageData = [];
                app.CurrentData = [];

                % Start reading data 
                while isvalid(app.SerialPort) && strcmp(app.SerialPort.Status, 'open')
     
                    data = readline(app.SerialPort);

                    % Display received data for debug
                    disp(['Received data: ', data]);

                    % cmd window received data 
                    splitData = strsplit(data, {':', 'V,', 'A'});
                    voltage = str2double(splitData{2}); % Extract voltage value
                    current = str2double(splitData{4}); % Extract current value

                    % Update time array
                    if isempty(app.Time)
                        app.Time = 0;
                    else
                        app.Time = [app.Time, app.Time(end) + 1]; % Increment time by 1 second
                    end

                    % Update data arrays
                    app.VoltageData = [app.VoltageData, voltage];
                    app.CurrentData = [app.CurrentData, current];

                    % Plot data
                    plot(app.UIAxes, app.Time, app.VoltageData, '-o', app.Time, app.CurrentData, '-o');
                    title(app.UIAxes, 'Voltage vs. Current');
                    xlabel(app.UIAxes, 'Time (s)');
                    ylabel(app.UIAxes, 'Value');
                    legend(app.UIAxes, {'Voltage (V)', 'Current (A)'});
                    grid(app.UIAxes, 'on');
                    drawnow; % Update the plot
                end
            catch e
                % Handle errors
                disp(['Error occurred: ', e.message]);
            finally
                % Close the serial port
                if ~isempty(app.SerialPort) && isvalid(app.SerialPort) && strcmp(app.SerialPort.Status, 'open')
                    fclose(app.SerialPort);
                    delete(app.SerialPort);
                end
            end
        end

        % Callback function for StopButton
        function stopButtonPushed(app, ~)
            % Close the serial port
            if ~isempty(app.SerialPort) && isvalid(app.SerialPort) && strcmp(app.SerialPort.Status, 'open')
                fclose(app.SerialPort);
                delete(app.SerialPort);
            end
        end
        % Callback function for SaveImageButton
        function saveImageButtonPushed(app, ~)
            % Save current plot as an image
            [filename, filepath] = uiputfile({'*.png', 'PNG Files (*.png)'; '*.jpg', 'JPEG Files (*.jpg)'}, 'Save Image');
            if ~isequal(filename, 0) && ~isequal(filepath, 0)
                fig = figure;
                plot(app.Time, app.VoltageData, '-o', app.Time, app.CurrentData, '-o');
                title('Voltage vs. Current');
                xlabel('Time (s)');
                ylabel('Value');
                legend({'Voltage (V)', 'Current (A)'});
                grid on;

                % Adjust x-axis limits to start from 0 seconds
                xlim([0, max(app.Time)]);

                % Save image to file
                saveas(fig, fullfile(filepath, filename));
                close(fig);
            end
        end

        % Callback function for SaveCSVButton
        function saveCSVButtonPushed(app, ~)
            % Save data to CSV file
            [filename, filepath] = uiputfile({'*.csv', 'Comma Separated Values (*.csv)'}, 'Save CSV');
            if ~isequal(filename, 0) && ~isequal(filepath, 0)
                fid = fopen(fullfile(filepath, filename), 'w');
                if fid == -1
                    disp('Error: Unable to create CSV file.');
                    return;
                end

                % Write header row
                fprintf(fid, 'Time,Voltage (V),Current (A)\n');

                % Write data rows
                data = [app.Time', app.VoltageData', app.CurrentData']; % Combine time, voltage, and current data
                for i = 1:size(data, 1)
                    fprintf(fid, '%f,%f,%f\n', data(i, :));
                end

                fclose(fid);
            end
        end

        % Callback function for app closing
        function appCloseRequest(app, ~)
            delete(app)
        end
    end
end
